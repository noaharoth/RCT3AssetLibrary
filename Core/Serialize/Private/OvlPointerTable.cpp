// OvlPointerTable.cpp

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
#include "OvlPointerTable.hpp"

using namespace RCT3Asset;

unsigned int OvlPointerTable::Search(unsigned int* ptr, unsigned int& file, FileSections(&sections)[2], RCT3Debugging::OutputLog& log)
{
	for (unsigned int f = 0; f < 2; f++)
	{
		file = f;

		for (unsigned int s = 0; s < 9; s++)
		{
			for (unsigned int e = 0; e < sections[f][s].Entries.size(); e++)
			{
				if (ptr >= (unsigned int*)sections[f][s].Entries[e].Data && ptr < (unsigned int*)(sections[f][s].Entries[e].Data + sections[f][s].Entries[e].Size))
				{
					return (unsigned int)ptr - (unsigned int)sections[f][s].Entries[e].Data + sections[f][s].Entries[e].Offset;
				}
			}
		}
	}

	log.Warning("OvlPointerTable::Search(..): did not find ptr " + STR((unsigned int)ptr) + " in file " + STR(file));

	return 0xFFFFFFFF;
}

void OvlPointerTable::CreatePointerTable(FileSections(&sections)[2], RCT3Debugging::OutputLog& log)
{
	unsigned int rawPtrSize = Pointers.size();

	log.Debug("OvlPointerTable::Create(..): Raw pointers count: " + STR(Pointers.size()));

	while (!Pointers.empty())
	{
		unsigned int* ptr = Pointers.front();
		Pointers.pop();


		unsigned int* actualData = *((unsigned int**)ptr);

		if (actualData == nullptr)
		{
			log.Warning("OvlPointerTable::CreatePointerTable(..): Data pointed to is nonexistent! (ptr address = " +
				STR((unsigned int)ptr) + ", " + "index = " + STR(rawPtrSize - Pointers.size()) + ")");
			continue;
		}

		unsigned int file = 0;
		unsigned int dataLocation = Search(actualData, file, sections, log);

		unsigned int dataLocationFile = file;

		if (dataLocation == 0xFFFFFFFF)
			dataLocation = 0;

		*ptr = dataLocation;

		unsigned int ptrLocation = Search(ptr, file, sections, log);
		PointerTable[file].push_back(ptrLocation);

		log.Debug("OvlPointerTable::CreatePointerTable(..): found ptr in file " + STR(file) + ", location " + STR(ptrLocation)
			+ ", data found in file " + STR(dataLocationFile) + ", location " + STR(dataLocation));
	}

	log.Debug("OvlPointerTable::Create(..): Final pointer count (common): " + STR(PointerTable[OvlType::Common].size()));

	log.Debug("OvlPointerTable::Create(..): Final pointer count (unique): " + STR(PointerTable[OvlType::Unique].size()));

	log.Debug("OvlPointerTable::Create(..): Final pointer count (total): " 
		+ STR(PointerTable[OvlType::Common].size() + PointerTable[OvlType::Unique].size()));

	log.Debug("OvlPointerTable::Create(..): Missing pointer count: " + 
		STR(rawPtrSize - (PointerTable[OvlType::Unique].size() + PointerTable[OvlType::Common].size())));

	log.Debug("OvlPointerTable::Create(..): created pointer tables!");
}