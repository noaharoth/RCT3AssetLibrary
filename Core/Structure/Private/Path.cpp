// Path.cpp

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
#include "Path.hpp"

using namespace RCT3Asset;

PathSection& PathSection::operator=(const std::string section)
{
	for (int i = 0; i < 4; i++)
	{
		_sections[i] = section;
	}

	return *this;
}

std::string& PathSection::operator[](unsigned int index)
{
	return _sections[index];
}

Path::Path() : Flags(0), Unknown01(0), Unknown02(1)
{
	Flags |= PathFlags::Default;
}

unsigned int Path::DataSize(unsigned int file)
{
	if (IsExtended())
		return sizeof(PathExtendedRawData);
	else
		return sizeof(PathRawData);

	return 0;
}

std::string Path::Name() const
{
	return _name;
}

void Path::Name(std::string name)
{
	_name = name;
}

void Path::SetUnderwaterFlag()
{
	Flags |= PathFlags::Underwater;
}

void Path::SetExtendedFlag()
{
	Flags |= PathFlags::Extended;
}

bool Path::IsExtended() const
{
	return (Flags & PathFlags::Extended);
}

std::string Path::GetNameID() const
{
	return _name + ":ptd";
}

void Path::CopyDataTo(OvlFile& ovl, void* raw, unsigned int headerIndex)
{
	ovl.AddString(GetNameID(), nullptr);


	if (IsExtended())
	{
		PathExtendedRawData* data = reinterpret_cast<PathExtendedRawData*>(raw);

		data->Flags = Flags;
		data->ResearchCategories = nullptr; // todo
		data->ResearchCategoryCount = 0; // todo
		data->Unknown01 = Unknown01;
		data->Unknown02 = Unknown02;
		ovl.AddString(_name, &data->Name);
		ovl.AddString(TextureA, &data->TextureA);
		ovl.AddString(TextureB, &data->TextureB);
		ovl.AddPointer(Ptr(data->Name));
		ovl.AddPointer(Ptr(data->TextureA));
		ovl.AddPointer(Ptr(data->TextureB));

		_copySection(ovl, Flat, data->Flat);
		_copySection(ovl, StraightA, data->StraightA);
		_copySection(ovl, StraightB, data->StraightB);
		_copySection(ovl, TurnU, data->TurnU);
		_copySection(ovl, TurnLA, data->TurnLA);
		_copySection(ovl, TurnLB, data->TurnLB);
		_copySection(ovl, TurnTA, data->TurnTA);
		_copySection(ovl, TurnTB, data->TurnTB);
		_copySection(ovl, TurnTC, data->TurnTC);
		_copySection(ovl, TurnX, data->TurnX);
		_copySection(ovl, CornerA, data->CornerA);
		_copySection(ovl, CornerB, data->CornerB);
		_copySection(ovl, CornerC, data->CornerC);
		_copySection(ovl, CornerD, data->CornerD);
		_copySection(ovl, Slope, data->Slope);
		_copySection(ovl, SlopeStraight, data->SlopeStraight);
		_copySection(ovl, SlopeStraightLeft, data->SlopeStraightLeft);
		_copySection(ovl, SlopeStraightRight, data->SlopeStraightRight);
		_copySection(ovl, SlopeMid, data->SlopeMid);

		_copySectionOptional(ovl, FlatFC, data->FlatFC);
		_copySectionOptional(ovl, SlopeFC, data->SlopeFC);
		_copySectionOptional(ovl, SlopeBC, data->SlopeBC);
		_copySectionOptional(ovl, SlopeTC, data->SlopeTC);
		_copySectionOptional(ovl, SlopeStraightFC, data->SlopeStraightFC);
		_copySectionOptional(ovl, SlopeStraightBC, data->SlopeStraightBC);
		_copySectionOptional(ovl, SlopeStraightTC, data->SlopeStraightTC);
		_copySectionOptional(ovl, SlopeStraightLeftFC, data->SlopeStraightLeftFC);
		_copySectionOptional(ovl, SlopeStraightLeftBC, data->SlopeStraightLeftBC);
		_copySectionOptional(ovl, SlopeStraightLeftTC, data->SlopeStraightLeftTC);
		_copySectionOptional(ovl, SlopeStraightRightFC, data->SlopeStraightRightFC);
		_copySectionOptional(ovl, SlopeStraightRightBC, data->SlopeStraightRightBC);
		_copySectionOptional(ovl, SlopeStraightRightTC, data->SlopeStraightRightTC);
		_copySectionOptional(ovl, SlopeMidFC, data->SlopeMidFC);
		_copySectionOptional(ovl, SlopeMidBC, data->SlopeMidBC);
		_copySectionOptional(ovl, SlopeMidTC, data->SlopeMidTC);

		if (Paving.length())
		{
			ovl.AddString(Paving, &data->Paving);
			ovl.AddPointer(Ptr(data->Paving));
		}

		Identifier id(GetNameID());
		id.AssignData(data);

		DataInfo info(ovl.GetStructureHeaderIndex(GetHeader()), data, id, 2);

		Reference txtRef(&data->Text, Text.NameID());
		txtRef.AssignOwner(info);
		ovl.AddString(txtRef.NameID(), nullptr);

		Reference gsiRef(&data->Icon, GsiIcon.NameID());
		gsiRef.AssignOwner(info);
		ovl.AddString(gsiRef.NameID(), nullptr);

		ovl.AddIdentifier(id, OvlType::Unique);
		ovl.AddDataInfo(info, OvlType::Unique);
		ovl.AddReference(txtRef, OvlType::Unique);
		ovl.AddReference(gsiRef, OvlType::Unique);
	}
	else
	{
		PathRawData* data = reinterpret_cast<PathRawData*>(raw);

		data->Flags = Flags;
		data->ResearchCategories = nullptr; // todo
		data->ResearchCategoryCount = 0; // todo
		ovl.AddString(_name, &data->Name);
		ovl.AddString(TextureA, &data->TextureA);
		ovl.AddString(TextureB, &data->TextureB);
		ovl.AddPointer(Ptr(data->Name));
		ovl.AddPointer(Ptr(data->TextureA));
		ovl.AddPointer(Ptr(data->TextureB));

		_copySection(ovl, Flat, data->Flat);
		_copySection(ovl, StraightA, data->StraightA);
		_copySection(ovl, StraightB, data->StraightB);
		_copySection(ovl, TurnU, data->TurnU);
		_copySection(ovl, TurnLA, data->TurnLA);
		_copySection(ovl, TurnLB, data->TurnLB);
		_copySection(ovl, TurnTA, data->TurnTA);
		_copySection(ovl, TurnTB, data->TurnTB);
		_copySection(ovl, TurnTC, data->TurnTC);
		_copySection(ovl, TurnX, data->TurnX);
		_copySection(ovl, CornerA, data->CornerA);
		_copySection(ovl, CornerB, data->CornerB);
		_copySection(ovl, CornerC, data->CornerC);
		_copySection(ovl, CornerD, data->CornerD);
		_copySection(ovl, Slope, data->Slope);
		_copySection(ovl, SlopeStraight, data->SlopeStraight);
		_copySection(ovl, SlopeStraightLeft, data->SlopeStraightLeft);
		_copySection(ovl, SlopeStraightRight, data->SlopeStraightRight);
		_copySection(ovl, SlopeMid, data->SlopeMid);

		Identifier id(GetNameID());
		id.AssignData(data);

		DataInfo info(ovl.GetStructureHeaderIndex(GetHeader()), data, id, 2);

		Reference txtRef(&data->Text, Text.NameID());
		txtRef.AssignOwner(info);
		ovl.AddString(txtRef.NameID(), nullptr);

		Reference gsiRef(&data->Icon, GsiIcon.NameID());
		gsiRef.AssignOwner(info);
		ovl.AddString(gsiRef.NameID(), nullptr);

		ovl.AddIdentifier(id, OvlType::Unique);
		ovl.AddDataInfo(info, OvlType::Unique);
		ovl.AddReference(txtRef, OvlType::Unique);
		ovl.AddReference(gsiRef, OvlType::Unique);
	}

	ovl.GetLog().Info("Path::CopyDataTo(..): Created path \"" + _name + "\"");
}

StructureHeader Path::GetHeader()
{
	StructureHeader h;
	h.LoaderType = OvlLoaderType::RCT3;
	h.StructID = "ptd";
	h.TypeNumber = 1;
	h.StructName = "PathType";
	return h;
}

void Path::_copySection(OvlFile& ovl, PathSection& section, PathSectionRawData& data)
{
	for (int i = 0; i < 4; i++)
	{
		ovl.AddString(section[i], &data.Sections[i]);
		ovl.AddPointer(Ptr(data.Sections[i]));
	}
}

void Path::_copySectionOptional(OvlFile& ovl, PathSection& section, PathSectionRawData& data)
{
	for (int i = 0; i < 4; i++)
	{
		if (section[i].length() > 0)
		{
			ovl.AddString(section[i], &data.Sections[i]);
			ovl.AddPointer(Ptr(data.Sections[i]));
		}
	}
}

void PathCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(Path::GetHeader());

	unsigned int size = 0;

	for (auto p : _structs)
	{
		size += p.DataSize(OvlType::Unique);
	}

	DataEntry& entry = ovl.CreateEntry(OvlType::Unique, 2, size);

	unsigned char* data = entry.Data;

	for (auto p : _structs)
	{

		p.CopyDataTo(ovl, data, headerIndex);
		data += p.DataSize(OvlType::Unique);

	}

}