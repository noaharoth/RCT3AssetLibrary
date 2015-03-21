// OvlPointerTable.h

#pragma once

#include "stdafx.hpp"
#include "OvlRaw.hpp"
#include "FileSections.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class OvlPointerTable
	{
	public:
		std::queue<unsigned int*> Pointers;
		std::vector<unsigned int> PointerTable[2];

		// * Searches for pointer within all DataSections.
		// @param ptr: The pointer to search for.
		// @param file: Function will assign the File number the pointer is location in.
		// @param sections: Reference to FileSections.
		unsigned int Search(unsigned int* ptr, unsigned int& file, FileSections(&sections)[2], RCT3Debugging::OutputLog& log);

		// Creates the pointer table.
		void CreatePointerTable(FileSections(&sections)[2], RCT3Debugging::OutputLog& log);
	};

#define Ptr(p) (reinterpret_cast<unsigned int*>(&(p)))

}