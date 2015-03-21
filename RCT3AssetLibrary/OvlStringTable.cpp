// OvlStringTable.cpp

#include "stdafx.hpp"
#include "OvlStringTable.hpp"

using namespace RCT3Asset;

unsigned int OvlStringTable::Size()
{
	unsigned int size = 0;
	for (auto i : Strings)
	{
		size += i.size() + 1;
	}

	return size;
}

void OvlStringTable::Create(DataEntry& entry, RCT3Debugging::OutputLog& log)
{
	log.Debug("OvlStringTable::Create(..): number of strings to create: " + STR(Strings.size()));

	OvlString str = reinterpret_cast<OvlString>(entry.Data);

	unsigned int loc = 0;

	for (auto i : Strings)
	{
		strcpy(str, i.c_str());
		str += i.size() + 1;
		Locations.push_back(loc);
		loc += i.size() + 1;
	}

	this->_entry = entry;

	log.Debug("OvlStringTable::Create(..): created string table!");
}

OvlString OvlStringTable::Find(std::string str, RCT3Debugging::OutputLog& log)
{
	auto it = Strings.find(str);
	if (it != Strings.end())
	{
		unsigned int index = std::distance(Strings.begin(), it);
		return reinterpret_cast<OvlString>(&_entry.Data[Locations[index]]);
	}

	log.Warning("OvlStringTable::Find(..): couldn't find string \"" + str + "\"");
	return nullptr;
}
