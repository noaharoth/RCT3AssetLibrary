// FileSections.hpp

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

#pragma once

#include "stdafx.hpp"
#include "OvlRaw.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	struct ExtraData
	{
		unsigned int Size;
		unsigned char* Data;

		ExtraData(unsigned int size, void* data);

		ExtraData();

	};

	struct DataEntry
	{
		unsigned int Size;
		unsigned int Offset;
		unsigned char* Data;

		DataEntry();
	};

	class DataSection
	{
	public:
		unsigned int Offset;
		std::vector<DataEntry> Entries;

		DataSection();

		// * Creates and returns DataEntry with specified size at the end of the vector.
		DataEntry& CreateAndAdd(unsigned int size);

		// * Creates and returns DataEntry with specified size at the beginning of the vector.
		DataEntry& CreateAndInsert(unsigned int size);

	};

	class FileSections
	{
	private:
		DataSection _sections[9];

	public:

		// * Returns a pointer to the DataSection at the specified index.
		DataSection& Get(unsigned int index);

		DataSection& operator[](unsigned int index);

		// * Updates all DataSection and DataEntry offsets, and returns the last DataSection offset.
		//   Required before creating PointerTable!
		unsigned int UpdateOffsets(unsigned int startingOffset, RCT3Debugging::OutputLog& log);

	};

}