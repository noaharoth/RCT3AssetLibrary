// OvlReferenceTable.cpp

#include "stdafx.hpp"
#include "OvlReferenceTable.hpp"

using namespace RCT3Asset;

Reference::Reference(void* location, std::string nameID) : _location((unsigned int*)location), _nameID(nameID)
{ 

}

unsigned int* Reference::Location()
{
	return _location;
}

std::string Reference::NameID()
{
	return _nameID;
}

DataInfo& Reference::Owner()
{
	return _owner;
}

unsigned int OvlReferenceTable::Size(unsigned int file)
{
	return (References[file].size() * sizeof(ReferenceRawData));
}

void OvlReferenceTable::Create(OvlStringTable& strTable, OvlPointerTable& pointerTable, OvlDataInfoTable& infoTable, RCT3Debugging::OutputLog& log)
{
	for (unsigned int i = 0; i < 2; i++)
	{

		if (_entries[i].Data != nullptr)
		{

			ReferenceRawData* raw = reinterpret_cast<ReferenceRawData*>(_entries[i].Data);

			for (unsigned int j = 0; j < References[i].size(); j++)
			{
				raw[j].Location = References[i][j].Location();
				pointerTable.Pointers.push(Ptr(raw[j].Location));

				DataInfo& owner = References[i][j].Owner();
				raw[j].Owner = infoTable.Find(owner, log);
				pointerTable.Pointers.push(Ptr(raw[j].Owner));

				raw[j].NameID = strTable.Find(References[i][j].NameID(), log);
				pointerTable.Pointers.push(Ptr(raw[j].NameID));

				log.Debug("OvlReferenceTable::Create(..): created Reference with name \"" + References[i][j].NameID() + "\"");
			}
		}
	}

	log.Debug("OvlReferenceTable::Create(..): created Reference tables!");
}