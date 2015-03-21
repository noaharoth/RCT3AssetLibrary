// FileSections.cpp

#include "stdafx.hpp"
#include "FileSections.hpp"

using namespace RCT3Asset;

DataEntry::DataEntry() : Size(0), Offset(0), Data(nullptr)
{

}

DataSection::DataSection() : Offset(0)
{ 
	
}

DataEntry& DataSection::CreateAndAdd(unsigned int size, RCT3Debugging::OutputLog& log)
{
	DataEntry entry;
	entry.Size = size;
	entry.Offset = 0;
	entry.Data = nullptr;
	if (size)
		entry.Data = new unsigned char[size]();
	Entries.push_back(entry);
	return Entries.back();
}

DataEntry& DataSection::CreateAndInsert(unsigned int size, RCT3Debugging::OutputLog& log)
{
	DataEntry entry;
	entry.Data = nullptr;
	entry.Size = size;
	entry.Offset = 0;
	if (size)
		entry.Data = new unsigned char[size]();
	Entries.insert(Entries.begin(), entry);
	return Entries.front();
}

DataSection& FileSections::Get(unsigned int index)
{
	if (index < 9)
		return _sections[index];

	return _sections[8];
}

DataSection& FileSections::operator[](unsigned int index)
{
	return Get(index);
}

unsigned int FileSections::UpdateOffsets(unsigned int startingOffset, RCT3Debugging::OutputLog& log)
{
	unsigned int currOffset = startingOffset;
	for (unsigned int i = 0; i < 9; i++)
	{
		for (unsigned int j = 0; j < _sections[i].Entries.size(); j++)
		{
			_sections[i].Entries[j].Offset = currOffset;
			currOffset += _sections[i].Entries[j].Size;
		}
		_sections[i].Offset = currOffset;
	}

	log.Debug("FileSections::UpdateOffsets(..): returned " + STR(currOffset));

	return currOffset;
}