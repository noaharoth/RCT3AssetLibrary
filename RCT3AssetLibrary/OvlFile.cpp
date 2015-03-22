// OvlFile.cpp

/*
* (C) Copyright 2015 Noah Roth
*
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the GNU Lesser General Public License
* (LGPL) version 2.1 which accompanies this distribution, and is available at
* http://www.gnu.org/licenses/lgpl-2.1.html
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
*/

#include "stdafx.hpp"
#include "OvlFile.hpp"

using namespace RCT3Asset;

void InitializeRCT3AssetLibrary(char* _arg)
{
	Magick::InitializeMagick(_arg);
}

void OvlFile::AddString(std::string str, OvlString* location)
{
	StringTable.Strings.insert(str);
	if (location != nullptr)
		FollowStrings.push(std::pair<std::string, OvlString*>(str, location));

	_log.Debug("AddString(..): added string \"" + str + "\"");
}

void OvlFile::AddPointer(unsigned int* pointer)
{
	PointerTable.Pointers.push(pointer);
}

void OvlFile::AddFileReference(std::string reference)
{
	FileReferences.push_back(reference);

	_log.Debug("OvlFile::AddFileReference(..): added file reference \"" + reference + "\"");
}

void OvlFile::AddIdentifier(Identifier id, unsigned int file)
{
	IdentifierTable.Identifiers[file].insert(id);
}

void OvlFile::AddDataInfo(DataInfo info, unsigned int file)
{
	DataInfoTable.DataInfos[file].push_back(info);
}

void OvlFile::AddReference(Reference reference, unsigned int file)
{
	ReferenceTable.References[file].push_back(reference);
}

DataEntry& OvlFile::CreateEntry(unsigned int file, unsigned int section, unsigned int size)
{
	return Sections[file][section].CreateAndAdd(size, _log);
}

RCT3Debugging::OutputLog& OvlFile::GetLog() const
{
	return _log;
}

unsigned int OvlFile::GetStructureHeaderIndex(StructureHeader header)
{
	auto it = std::find(StructureHeaders.begin(), StructureHeaders.end(), header);

	if (it != StructureHeaders.end())
	{
		return std::distance(StructureHeaders.begin(), it);
	}

	_log.Warning("OvlFile::GetStructureHeaderIndex(..): Couldn't find index. This will probably end badly...");

	return 0xFFFFFFFF;
}

unsigned int OvlFile::AddStructureHeader(StructureHeader header)
{
	StructureHeaders.push_back(header);

	return StructureHeaders.size() - 1;
}

ExtraData OvlFile::CreateAndAddExtraData(unsigned int size, unsigned int file)
{
	ExtraData data;
	data.Size = size;
	data.Data = new unsigned char[size]();
	OvlExtraData[file].push_back(data);
	return data;
}

void OvlFile::_fixStrings()
{
	while (!FollowStrings.empty())
	{
		auto currString = FollowStrings.front();
		FollowStrings.pop();

		OvlString* source = currString.second;

		*source = StringTable.Find(currString.first, _log);
	}
}

void OvlFile::_createIdentifierTables()
{
	unsigned int size = IdentifierTable.Size(COMMON);

	DataEntry& commonEntry = Sections[COMMON][2].CreateAndInsert(size, _log);
	IdentifierTable.AssignEntry(commonEntry, COMMON);

	size = IdentifierTable.Size(UNIQUE);

	DataEntry& uniqueEntry = Sections[UNIQUE][2].CreateAndInsert(size, _log);
	IdentifierTable.AssignEntry(uniqueEntry, UNIQUE);

}

void OvlFile::_createDataInfoTables()
{
	unsigned int size = DataInfoTable.Size(COMMON);

	DataEntry& commonEntry = Sections[COMMON][2].CreateAndInsert(size, _log);
	DataInfoTable.AssignEntry(commonEntry, COMMON);

	size = DataInfoTable.Size(UNIQUE);

	DataEntry& uniqueEntry = Sections[UNIQUE][2].CreateAndInsert(size, _log);
	DataInfoTable.AssignEntry(uniqueEntry, UNIQUE);
}

void OvlFile::_createReferenceTables()
{
	unsigned int size;

	if ((size = ReferenceTable.Size(COMMON)) > 0)
	{
		DataEntry& commonEntry = Sections[COMMON][2].CreateAndInsert(size, _log);
		ReferenceTable.AssignEntry(commonEntry, COMMON);
	}

	if ((size = ReferenceTable.Size(UNIQUE)) > 0)
	{
		DataEntry& uniqueEntry = Sections[UNIQUE][2].CreateAndInsert(size, _log);
		ReferenceTable.AssignEntry(uniqueEntry, UNIQUE);
	}
}

void OvlFile::_createPointerTables()
{
	unsigned int commonOffset = Sections[COMMON].UpdateOffsets(0, _log);
	Sections[UNIQUE].UpdateOffsets(commonOffset, _log);

	PointerTable.CreatePointerTable(Sections, _log);
}

void OvlFile::CreateTables()
{
	DataEntry& stringTableEntry = Sections[COMMON][0].CreateAndInsert(StringTable.Size(), _log);
	StringTable.Create(stringTableEntry, _log);

	_fixStrings();

	_createReferenceTables();
	_createDataInfoTables();
	_createIdentifierTables();

	IdentifierTable.Create(PointerTable, StringTable, _log);
	DataInfoTable.Create(IdentifierTable, PointerTable, _log);
	ReferenceTable.Create(StringTable, PointerTable, DataInfoTable, _log);

	_createPointerTables();

	_log.Info("OvlFile::CreateTables(..): Created all data tables!");
}

void OvlFile::Save(std::string filename)
{
	
	CreateTables();

	std::string commonFileName = filename + ".common.ovl";
	std::string uniqueFileName = filename + ".unique.ovl";

	FILE* commonFile, *uniqueFile;

	commonFile = fopen(commonFileName.c_str(), "wb");
	uniqueFile = fopen(uniqueFileName.c_str(), "wb");

	if (!commonFile)
	{
		_log.Error("OvlFile::Save(..): unable to open file \"" + commonFileName + "\" for writing!");
		return;
	}

	if (!uniqueFile)
	{
		_log.Error("OvlFile::Save(..): unable to open file \"" + uniqueFileName + "\" for writing!");
		return;
	}

	_log.Info("OvlFile::Save(..): opened \"" + commonFileName + "\" and \"" + uniqueFileName + "\" for writing.");

	Header.StructureCount = StructureHeaders.size();

	// write header
	fwrite(&Header.Signature, sizeof(Header.Signature), 1, commonFile);
	fwrite(&Header.Reserved, sizeof(Header.Reserved), 1, commonFile);
	fwrite(&Header.Version, sizeof(Header.Version), 1, commonFile);
	fwrite(&Header.ReferenceCount, sizeof(Header.ReferenceCount), 1, commonFile);
	fwrite(&Header.Unknown01, sizeof(Header.Unknown01), 1, commonFile);
	fwrite(&Header.StructureCount, sizeof(Header.StructureCount), 1, commonFile);

	Header.ReferenceCount = FileReferences.size();

	fwrite(&Header.Signature, sizeof(Header.Signature), 1, uniqueFile);
	fwrite(&Header.Reserved, sizeof(Header.Reserved), 1, uniqueFile);
	fwrite(&Header.Version, sizeof(Header.Version), 1, uniqueFile);
	fwrite(&Header.ReferenceCount, sizeof(Header.ReferenceCount), 1, uniqueFile);

	// write references to unique file
	for (auto r : FileReferences)
	{
		unsigned short size = r.size();
		fwrite(&size, sizeof(size), 1, uniqueFile);
		fwrite(r.c_str(), r.length(), 1, uniqueFile);
	}

	fwrite(&Header.Unknown01, sizeof(Header.Unknown01), 1, uniqueFile);
	fwrite(&Header.StructureCount, sizeof(Header.StructureCount), 1, uniqueFile);

	for (auto h : StructureHeaders)
	{
		unsigned short len = sizeof(h.LoaderType);

		fwrite(&len, sizeof(len), 1, commonFile);
		fwrite(&len, sizeof(len), 1, uniqueFile);

		fwrite(&h.LoaderType, sizeof(h.LoaderType), 1, commonFile);
		fwrite(&h.LoaderType, sizeof(h.LoaderType), 1, uniqueFile);

		len = (unsigned short)h.StructName.length();

		fwrite(&len, sizeof(len), 1, commonFile);
		fwrite(&len, sizeof(len), 1, uniqueFile);

		fwrite(h.StructName.c_str(), h.StructName.length(), 1, commonFile);
		fwrite(h.StructName.c_str(), h.StructName.length(), 1, uniqueFile);

		fwrite(&h.TypeNumber, sizeof(h.TypeNumber), 1, commonFile);
		fwrite(&h.TypeNumber, sizeof(h.TypeNumber), 1, uniqueFile);

		len = (unsigned short)h.StructID.length();

		fwrite(&len, sizeof(len), 1, commonFile);
		fwrite(&len, sizeof(len), 1, uniqueFile);

		fwrite(h.StructID.c_str(), h.StructID.length(), 1, commonFile);
		fwrite(h.StructID.c_str(), h.StructID.length(), 1, uniqueFile);
	}

	for (unsigned int i = 0; i < 9; i++)
	{
		unsigned int count = Sections[COMMON][i].Entries.size();
		fwrite(&count, sizeof(count), 1, commonFile);
		count = Sections[UNIQUE][i].Entries.size();
		fwrite(&count, sizeof(count), 1, uniqueFile);
	}

	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int j = 0; j < Sections[COMMON][i].Entries.size(); j++)
		{
			unsigned int size = Sections[COMMON][i].Entries[j].Size;

			_log.Debug("OvlFile::Save(..): File COMMON, Section " + STR(i) + ", Entry " + STR(j) + ": Size = " + STR(size)
				+ ", File IO Offset = " + STR((int)ftell(commonFile)));

			fwrite(&size, sizeof(size), 1, commonFile);

			if (size)
				fwrite(Sections[COMMON][i].Entries[j].Data, size, 1, commonFile);
		}
	}

	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int j = 0; j < Sections[UNIQUE][i].Entries.size(); j++)
		{
			unsigned int size = Sections[UNIQUE][i].Entries[j].Size;

			_log.Debug("OvlFile::Save(..): File UNIQUE, Section " + STR(i) + ", Entry " + STR(j) + ": Size = " + STR(size)
				+ ", File IO Offset = " + STR((int)ftell(uniqueFile)));

			fwrite(&size, sizeof(size), 1, uniqueFile);

			if (size)
				fwrite(Sections[UNIQUE][i].Entries[j].Data, size, 1, uniqueFile);
		}
	}

	unsigned int pointerTableSize = PointerTable.PointerTable[COMMON].size();
	fwrite(&pointerTableSize, sizeof(pointerTableSize), 1, commonFile);
	for (unsigned int i = 0; i < pointerTableSize; i++)
	{
		unsigned int pointer = PointerTable.PointerTable[COMMON][i];
		fwrite(&pointer, sizeof(pointer), 1, commonFile);
	}

	// Extra data

	for (unsigned int i = 0; i < OvlExtraData[COMMON].size(); i++)
	{
		fwrite(&OvlExtraData[COMMON][i].Size, sizeof(unsigned int), 1, commonFile);
		fwrite(OvlExtraData[COMMON][i].Data, OvlExtraData[COMMON][i].Size, 1, commonFile);
	}

	for (unsigned int i = 0; i < OvlExtraData[UNIQUE].size(); i++)
	{
		fwrite(&OvlExtraData[UNIQUE][i].Size, sizeof(unsigned int), 1, uniqueFile);
		fwrite(OvlExtraData[UNIQUE][i].Data, OvlExtraData[UNIQUE][i].Size, 1, uniqueFile);
	}

	// Done!

	_log.Info("OvlFile::Save(..): Successfully wrote OVL data to files!");

	fflush(commonFile);
	fflush(uniqueFile);
	fclose(commonFile);
	fclose(uniqueFile);

	/*std::ofstream commonFile, uniqueFile;

	commonFile.open(commonFileName, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
	uniqueFile.open(uniqueFileName, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);

	if (!commonFile.is_open())
	{
		_log.Error("OvlFile::Save(..): unable to open file \"" + commonFileName + "\" for writing!");
		return;
	}

	if (!uniqueFile.is_open())
	{
		_log.Error("OvlFile::Save(..): unable to open file \"" + uniqueFileName + "\" for writing!");
		return;
	}

	_log.Info("OvlFile::Save(..): opened \"" + commonFileName + "\" and \"" + uniqueFileName + "\" for writing.");

	Header.StructureCount = StructureHeaders.size();

	// write header
	commonFile.write((const char*)&Header.Signature, sizeof(Header.Signature));
	commonFile.write((const char*)&Header.Reserved, sizeof(Header.Reserved));
	commonFile.write((const char*)&Header.Version, sizeof(Header.Version));
	commonFile.write((const char*)&Header.ReferenceCount, sizeof(Header.ReferenceCount));
	commonFile.write((const char*)&Header.Unknown01, sizeof(Header.Unknown01));
	commonFile.write((const char*)&Header.StructureCount, sizeof(Header.StructureCount));

	Header.ReferenceCount = FileReferences.size();

	uniqueFile.write((const char*)&Header.Signature, sizeof(Header.Signature));
	uniqueFile.write((const char*)&Header.Reserved, sizeof(Header.Reserved));
	uniqueFile.write((const char*)&Header.Version, sizeof(Header.Version));
	uniqueFile.write((const char*)&Header.ReferenceCount, sizeof(Header.ReferenceCount));

	// write references to unique file
	for (auto r : FileReferences)
	{
		unsigned short size = r.size();
		uniqueFile.write((const char*)&size, sizeof(unsigned short));
		uniqueFile << r;
	}

	uniqueFile.write((const char*)&Header.Unknown01, sizeof(Header.Unknown01));
	uniqueFile.write((const char*)&Header.StructureCount, sizeof(Header.StructureCount));

	// write structure headers

	for (auto h : StructureHeaders)
	{
		unsigned short len = sizeof(h.LoaderType);
		commonFile.write((const char*)&len, sizeof(len));
		uniqueFile.write((const char*)&len, sizeof(len));
		commonFile.write((const char*)&h.LoaderType, sizeof(h.LoaderType));
		uniqueFile.write((const char*)&h.LoaderType, sizeof(h.LoaderType));
		len = (unsigned short)h.StructName.length();
		commonFile.write((const char*)&len, sizeof(len));
		uniqueFile.write((const char*)&len, sizeof(len));
		commonFile.write(h.StructName.c_str(), h.StructName.length());
		uniqueFile.write(h.StructName.c_str(), h.StructName.length());
		commonFile.write((const char*)&h.TypeNumber, sizeof(h.TypeNumber));
		uniqueFile.write((const char*)&h.TypeNumber, sizeof(h.TypeNumber));
		len = (unsigned short)h.StructID.length();
		commonFile.write((const char*)&len, sizeof(len));
		uniqueFile.write((const char*)&len, sizeof(len));
		commonFile.write(h.StructID.c_str(), h.StructID.length());
		uniqueFile.write(h.StructID.c_str(), h.StructID.length());
	}

	// data entry counts

	for (unsigned int i = 0; i < 9; i++)
	{
		unsigned int count = Sections[COMMON][i].Entries.size();
		commonFile.write((const char*)&count, sizeof(count));
		count = Sections[UNIQUE][i].Entries.size();
		uniqueFile.write((const char*)&count, sizeof(count));
	}

	// serialize data

	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int j = 0; j < Sections[COMMON][i].Entries.size(); j++)
		{
			unsigned int size = Sections[COMMON][i].Entries[j].Size;

			_log.Debug("OvlFile::Save(..): File COMMON, Section " + STR(i) + ", Entry " + STR(j) + ": Size = " + STR(size)
				+ ", File IO Offset = " + STR(commonFile.tellp()));

			commonFile.write((const char*)&size, sizeof(size));

			if (size)
				commonFile.write((const char*)Sections[COMMON][i].Entries[j].Data, size);
		}
	}

	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int j = 0; j < Sections[UNIQUE][i].Entries.size(); j++)
		{
			unsigned int size = Sections[UNIQUE][i].Entries[j].Size;

			_log.Debug("OvlFile::Save(..): File UNIQUE, Section " + STR(i) + ", Entry " + STR(j) + ": Size = " + STR(size)
				+ ", File IO Offset = " + STR(uniqueFile.tellp()));

			uniqueFile.write((const char*)&size, sizeof(size));
			uniqueFile.write((const char*)Sections[UNIQUE][i].Entries[j].Data, size);
		}
	}

	// write pointer table

	unsigned int pointerTableSize = PointerTable.PointerTable[COMMON].size();
	commonFile.write((const char*)&pointerTableSize, sizeof(pointerTableSize));
	for (unsigned int i = 0; i < pointerTableSize; i++)
	{
		unsigned int pointer = PointerTable.PointerTable[COMMON][i];
		commonFile.write((const char*)&pointer, sizeof(pointer));
	}

	pointerTableSize = PointerTable.PointerTable[UNIQUE].size();
	uniqueFile.write((const char*)&pointerTableSize, sizeof(pointerTableSize));
	for (unsigned int i = 0; i < pointerTableSize; i++)
	{
		unsigned int pointer = PointerTable.PointerTable[UNIQUE][i];
		uniqueFile.write((const char*)&pointer, sizeof(pointer));
	}

	for (unsigned int i = 0; i < OvlExtraData[COMMON].size(); i++)
	{
		commonFile.write((const char*)&OvlExtraData[COMMON][i].Size, sizeof(unsigned int));
		commonFile.write((const char*)OvlExtraData[COMMON][i].Data, OvlExtraData[COMMON][i].Size);
	}

	for (unsigned int i = 0; i < OvlExtraData[UNIQUE].size(); i++)
	{
		uniqueFile.write((const char*)&OvlExtraData[UNIQUE][i].Size, sizeof(unsigned int));
		uniqueFile.write((const char*)OvlExtraData[UNIQUE][i].Data, OvlExtraData[UNIQUE][i].Size);
	}

	// Done!

	_log.Info("OvlFile::Save(..): Successfully wrote OVL data to files!");

	commonFile.close();
	uniqueFile.close();*/
}

OvlFile::~OvlFile()
{
	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < 9; j++)
		{
			for (auto entry : Sections[i][j].Entries)
			{
				if (entry.Data != nullptr)
				{
					delete[] entry.Data;
				}
			}
		}

		for (auto extra : OvlExtraData[i])
		{
			if (extra.Data != nullptr)
			{
				delete[] extra.Data;
			}
		}

	}

}