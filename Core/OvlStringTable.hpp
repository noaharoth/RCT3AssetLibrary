// OvlStringTable.hpp

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