// OvlIdentifierTable.hpp

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
#include "OvlPointerTable.hpp"
#include "OvlStringTable.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class Identifier
	{
	private:
		std::string _nameID;
		unsigned char* _dataPtr;
		bool _isPointer;

	public:
		Identifier() { }

		Identifier(std::string nameID);

		void AssignData(void* data);

		std::string NameID() const;

		unsigned char* Data();

		unsigned int IsPointer();

		bool operator==(const Identifier& other) const
		{
			return (_nameID == other._nameID &&
				_dataPtr == other._dataPtr &&
				_isPointer == other._isPointer);
		}
	};

	struct IdentifierSorter
	{
		static bool icompare_pred(char a, char b);

		bool icompare(const std::string& a, const std::string& b) const;

		bool operator()(const Identifier& id1, const Identifier& id2) const;
	};

	class OvlIdentifierTable
	{
	private:
		DataEntry _entries[2];
	public:
		std::set<Identifier, IdentifierSorter> Identifiers[2];
		std::vector<unsigned int> Locations[2];

		// * Returns the size of the OvlIdentifierTable data in the specified file.
		unsigned int Size(unsigned int file);

		// * Creates the OvlIdentifierTable data.
		void Create(OvlPointerTable& pointerTable, OvlStringTable& stringTable, RCT3Debugging::OutputLog& log);

		// * Finds and returns the Identifier in a raw data format pointer in the DataEntry.
		IdentifierRawData* Find(Identifier id, RCT3Debugging::OutputLog& log);

		void AssignEntry(DataEntry entry, unsigned int file)
		{
			if (entry.Data != nullptr)
				_entries[file] = entry;
		}
	};

}