// OvlStringTable.h

#pragma once

#include "stdafx.hpp"
#include "OvlRaw.hpp"
#include "FileSections.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class OvlStringTable
	{
	private:
		DataEntry _entry;
	public:
		std::set<std::string> Strings;
		std::vector<unsigned int> Locations;

		// * Returns the size of the StringTable.
		unsigned int Size();

		// * Writes string data to specified DataSection (must be allocated beforehand!).
		void Create(DataEntry& entry, RCT3Debugging::OutputLog& log);

		// Finds the std::string data in the DataEntry data, and returns an OvlString for that data.
		OvlString Find(std::string str, RCT3Debugging::OutputLog& log);
	};

}