// OvlReferenceTable.h

#pragma once

#include "stdafx.hpp"
#include "OvlRaw.hpp"
#include "OvlDataInfoTable.hpp"
#include "OvlStringTable.hpp"
#include "OvlPointerTable.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class DataInfo;

	class Reference
	{
		friend class DataInfo;
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

	class OvlReferenceTable
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