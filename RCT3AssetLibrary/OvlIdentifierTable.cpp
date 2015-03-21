// OvlIdentifierTable.cpp

#include "stdafx.hpp"
#include "OvlIdentifierTable.hpp"

using namespace RCT3Asset;

Identifier::Identifier(std::string nameID) : _nameID(nameID), _dataPtr(nullptr), _isPointer(false) { }

void Identifier::AssignData(void* data)
{
	_dataPtr = (unsigned char*)data;
	_isPointer = true;
}

std::string Identifier::NameID() const
{
	return _nameID;
}

unsigned char* Identifier::Data()
{
	return _dataPtr;
}

unsigned int Identifier::IsPointer()
{
	return _isPointer ? 1 : 0;
}

bool IdentifierSorter::icompare_pred(char a, char b)
{
	return std::tolower(a) < std::tolower(b);
}

bool IdentifierSorter::icompare(const std::string& a, const std::string& b)
{
	return std::lexicographical_compare(a.begin(), a.end(),
		b.begin(), b.end(), icompare_pred);
}

bool IdentifierSorter::operator()(const Identifier& id1, const Identifier& id2)
{

	std::string id1n = id1.NameID();
	std::string id2n = id2.NameID();
	return icompare(id1n, id2n);
}

unsigned int OvlIdentifierTable::Size(unsigned int file)
{
	return (Identifiers[file].size() * sizeof(IdentifierRawData));
}

void OvlIdentifierTable::Create(OvlPointerTable& pointerTable, OvlStringTable& stringTable, RCT3Debugging::OutputLog& log)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		if (_entries[i].Data != nullptr)
		{

			IdentifierRawData* idData = reinterpret_cast<IdentifierRawData*>(_entries[i].Data);

			for (auto id : Identifiers[i])
			{
				idData->IsPointer = id.IsPointer();

				idData->Data = id.Data();
				pointerTable.Pointers.push(Ptr(idData->Data));

				idData->NameID = stringTable.Find(id.NameID(), log);
				pointerTable.Pointers.push(Ptr(idData->NameID));

				Locations[i].push_back((unsigned int)idData - (unsigned int)_entries[i].Data);

				idData++;

				log.Debug("OvlIdentifierTable::Create(..): created Identifier \"" + id.NameID() + "\"");
			}
		}
	}

	log.Debug("OvlIdentifierTable::Create(..): created Identifier tables!");
}

IdentifierRawData* OvlIdentifierTable::Find(Identifier id, RCT3Debugging::OutputLog& log)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		auto it = Identifiers[i].find(id);
		if (it != Identifiers[i].end())
		{
			unsigned int index = std::distance(Identifiers[i].begin(), it);
			unsigned int location = Locations[i][index];
			return reinterpret_cast<IdentifierRawData*>(&(_entries[i].Data[location]));
		}
	}

	log.Warning("OvlIdentifierTable::Find(..): couldn't find identifier \"" + id.NameID() + "\"");
	return nullptr;
}