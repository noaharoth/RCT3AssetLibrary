// OvlReferenceTable.hpp

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
#include "OvlDataInfoTable.hpp"
#include "OvlStringTable.hpp"
#include "OvlPointerTable.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class R3AL_API DataInfo;

	class R3AL_API Reference
	{
	private:
		unsigned int* _location;
		std::string _nameID;
		DataInfo _owner;

	public:

		Reference(void* location, std::string nameID);

		unsigned int* Location();

		std::string NameID();

		DataInfo& Owner();

		void AssignOwner(DataInfo info)
		{
			_owner = info;
		}
	};

	class R3AL_API OvlReferenceTable
	{
	private:
		DataEntry _entries[2];
	public:
		std::vector<Reference> References[2];

		// * Returns the size of the OvlReferenceTable in the specified file.
		unsigned int Size(unsigned int file);

		// * Creates the OvlReferenceTable data.
		void Create(OvlStringTable& strTable, OvlPointerTable& pointerTable, OvlDataInfoTable& infoTable, RCT3Debugging::OutputLog& log);

		void AssignEntry(DataEntry entry, unsigned int file)
		{
			if (entry.Data != nullptr)
				_entries[file] = entry;
		}
	};

}