// OvlDataInfoTable.h

#pragma once

#include "stdafx.hpp"
#include "FileSections.hpp"
#include "OvlRaw.hpp"
#include "OvlIdentifierTable.hpp"
#include "OvlPointerTable.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class DataInfo
	{
	private:
		unsigned int _structHeaderIndex;
		unsigned int _refCount;
		unsigned char* _dataPtr;
		Identifier _id;
		bool _noID;

	public:

		std::vector<ExtraData> ExtraData;

		DataInfo(unsigned int structHeaderIndex, void* data, Identifier id, unsigned int refCount);

		DataInfo(unsigned int structHeaderIndex, void* data, unsigned int refCount);

		DataInfo() { }

		unsigned int ReferenceCount();
		
		bool HasID() const;

		Identifier& ID();

		unsigned char* DataPtr(); 

		unsigned int StructureHeaderIndex();

		bool operator==(const DataInfo& other) const
		{
			return (_structHeaderIndex == other._structHeaderIndex &&
				_refCount == other._refCount &&
				_dataPtr == other._dataPtr &&
				_id == other._id);
		}
	};

	class OvlDataInfoTable
	{
	private:
		DataEntry _entries[2];
	public:
		std::vector<DataInfo> DataInfos[2];

		// * Returns the size of the OvlDataInfoTable in the specified file.
		unsigned int Size(unsigned int file);

		// * Creates the OvlDataInfoTable data.
		void Create(OvlIdentifierTable& idTable, OvlPointerTable& pointerTable, RCT3Debugging::OutputLog& log);

		// * Finds and returns the DataInfo in raw data format located in the created OvlDataInfoTable.
		DataInfoRawData* Find(DataInfo info, RCT3Debugging::OutputLog& log);

		void AssignEntry(DataEntry entry, unsigned int file)
		{
			if (entry.Data != nullptr)
				_entries[file] = entry;
		}
	};

}