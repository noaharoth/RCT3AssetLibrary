// OvlPointerTable.hpp

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
#include "FileSections.hpp"
#include <OutputLog.hpp>

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