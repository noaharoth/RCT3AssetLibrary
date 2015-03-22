// OvlDataInfoTable.cpp

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

#include "stdafx.hpp"
#include "OvlDataInfoTable.hpp"

using namespace RCT3Asset;

DataInfo::DataInfo(unsigned int structHeaderIndex, void* data, Identifier id, unsigned int refCount) 
	: _structHeaderIndex(structHeaderIndex), _dataPtr((unsigned char*)data), _id(id), _refCount(refCount), _noID(false)
{ 

}

DataInfo::DataInfo(unsigned int structHeaderIndex, void* data, unsigned int refCount)
	: _structHeaderIndex(structHeaderIndex), _dataPtr((unsigned char*)data), _noID(true), _refCount(refCount)
{

}

unsigned int DataInfo::ReferenceCount()
{
	return _refCount;
}

bool DataInfo::HasID() const
{
	return !_noID;
}

Identifier& DataInfo::ID()
{
	return _id;
}

unsigned char* DataInfo::DataPtr()
{
	return _dataPtr;
}

unsigned int DataInfo::StructureHeaderIndex()
{
	return _structHeaderIndex;
}

unsigned int OvlDataInfoTable::Size(unsigned int file)
{
	return (DataInfos[file].size() * sizeof(DataInfoRawData));
}

void OvlDataInfoTable::Create(OvlIdentifierTable& idTable, OvlPointerTable& pointerTable, RCT3Debugging::OutputLog& log)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		if (_entries[i].Data != nullptr)
		{

			DataInfoRawData* raw = reinterpret_cast<DataInfoRawData*>(_entries[i].Data);

			for (unsigned int j = 0; j < DataInfos[i].size(); j++)
			{
				raw[j].Data = DataInfos[i][j].DataPtr();
				pointerTable.Pointers.push(Ptr(raw[j].Data));

				raw[j].ExtraDataCount = DataInfos[i][j].ExtraData.size();
				raw[j].ReferenceCount = DataInfos[i][j].ReferenceCount();
				raw[j].StructureHeaderIndex = DataInfos[i][j].StructureHeaderIndex();

				if (DataInfos[i][j].HasID())
				{
					raw[j].ID = idTable.Find(DataInfos[i][j].ID(), log);
					pointerTable.Pointers.push(Ptr(raw[j].ID));
				}

				log.Debug("OvlDataInfoTable::Create(..): created DataInfo with ID name \"" + DataInfos[i][j].ID().NameID() + "\"");
			}
		}
	}

	log.Debug("OvlDataInfoTable::Create(..): created DataInfo tables!");
}

DataInfoRawData* OvlDataInfoTable::Find(DataInfo info, RCT3Debugging::OutputLog& log)
{
	for (unsigned int i = 0; i < 2; i++)
	{

		auto it = std::find(DataInfos[i].begin(), DataInfos[i].end(), info);

		if (it != DataInfos[i].end())
		{
			unsigned int index = std::distance(DataInfos[i].begin(), it);
			return &(((DataInfoRawData*)_entries[i].Data)[index]);
		}
	}

	log.Warning("OvlDataInfoTable::Create(..): couldn't find DataInfo with ID \"" + info.ID().NameID() + "\"");

	return nullptr;
}