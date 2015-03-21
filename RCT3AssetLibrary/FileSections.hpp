// FileSections.h

#pragma once

#include "stdafx.hpp"
#include "OvlRaw.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

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

		// * Creates and returns DataEntry at the end of the vector.
		DataEntry& CreateAndAdd(unsigned int size, RCT3Debugging::OutputLog& log);

		// * Creates and returns DataEntry at the beginning of the vector.
		DataEntry& CreateAndInsert(unsigned int size, RCT3Debugging::OutputLog& log);

	};

	class FileSections
	{
	private:
		DataSection _sections[9];

	public:

		// * Returns a pointer to the DataSection at the specified index.
		DataSection& Get(unsigned int index);

		DataSection& operator[](unsigned int index);

		// * Updates all DataSection and DataEntry offsets. Required before creating PointerTable!
		unsigned int UpdateOffsets(unsigned int startingOffset, RCT3Debugging::OutputLog& log);

	};

}