// SceneryItem.cpp

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
#include "SceneryItem.hpp"

using namespace RCT3Asset;

PositionData::PositionData() : Flags(0), HeightMin(0), HeightMax(0), SupportsType(0)
{

}

unsigned int PositionData::ActualHeight() const
{
	return HeightMax - HeightMin;
}

unsigned int PositionData::DataSize() const
{
	unsigned int h = ActualHeight();
	return ((h / 32) + (h % 32) ? 1 : 0) * 4;
}

void PositionData::CopyDataTo(OvlFile& ovl, PositioningRawData* pos, unsigned int* data)
{
	pos->Flags = Flags;
	pos->HeightMax = HeightMax;
	pos->HeightMin = HeightMin;
	pos->SupportsType = SupportsType;
	pos->Data = data;
	if (data)
		ovl.AddPointer(Ptr(pos->Data));

	unsigned int h = ActualHeight();
	if (h) {
		for (int i = 0; i < h / 32; i++) {
			data[i] = 0xFFFFFFFF;
			if (h % 32) {
				data[h / 32] = (1 << (h % 32)) - 1;
			}
		}
	}
}

SceneryItem::SceneryItem()
{
	Unknown01 = 0;
	Flags = 0;
	AddonPack = 0;
	Unknown02 = 0;
	Cost = 0;
	Refund = 0;
	Unknown03 = 0;
	Unknown04 = 0;
	Unknown05 = 0;
	StallUnknown01 = 0;
	StallUnknown02 = 0;
	Unknown06 = 0;
	Unknown07 = 0;
	Unknown08 = 0;
	Unknown09 = 0;
	Unknown10 = 0;
	Unknown11 = 0;
	Unknown12 = 0;
	Unknown13 = 0;
	Unknown14 = 0;

	PositioningType = SIDPositionType::Tile_Full;
	XSquareCount = 1;
	ZSquareCount = 1;
	Size.X = 4.0f;
	Size.Y = 4.0f;
	Size.Z = 4.0f;
	SceneryItemType = SIDType::Scenery_Small;
}

void SceneryItem::Name(std::string name)
{
	_name = name;
}

std::string SceneryItem::Name() const
{
	return _name;
}

std::string SceneryItem::GetNameID() const
{
	return _name + ":sid";
}

unsigned int SceneryItem::GetDataSize(unsigned int file)
{
	if (file == UNIQUE)
	{
		unsigned int size = sizeof(SceneryItemRawData);
		size += Svds.size() * sizeof(SvdPtr);
		return size;
	}

	unsigned int commonsize = XSquareCount * ZSquareCount * sizeof(PositioningRawData);

	if (PositioningData.size())
	{
		if (PositioningData.size() > 1)
		{
			for (int i = 0; i < PositioningData.size(); i++)
			{
				if (PositioningData[i].ActualHeight())
					commonsize += PositioningData[i].DataSize();
			}
		}
		else
		{
			if (PositioningData[0].ActualHeight())
				commonsize += XSquareCount * ZSquareCount * PositioningData[0].DataSize();
		}
	}

	commonsize += Parameters.size() * sizeof(ParameterRawData);

	return commonsize;
}

void SceneryItem::CopyDataTo(OvlFile& ovl, unsigned char* unique, unsigned char* common, unsigned int headerIndex)
{
	ovl.AddString(GetNameID(), nullptr);

	SceneryItemRawData* sid = reinterpret_cast<SceneryItemRawData*>(unique);
	unique += sizeof(SceneryItemRawData);

	unsigned int referenceCount = 2;

	if (GsiGroupIcon.NameID().length())
		referenceCount++;

	if (TxtGroupName.NameID().length())
		referenceCount++;

	referenceCount += Svds.size();

	Identifier id(GetNameID());
	id.AssignData(sid);

	DataInfo info(headerIndex, sid, id, referenceCount);

	Reference txtNameRef(&sid->TxtName, TxtName.NameID());
	ovl.AddString(TxtName.NameID(), nullptr);
	txtNameRef.AssignOwner(info);

	Reference gsiIconRef(&sid->GsiIcon, GsiIcon.NameID());
	ovl.AddString(GsiIcon.NameID(), nullptr);
	gsiIconRef.AssignOwner(info);

	if (GsiGroupIcon.NameID().length())
	{
		Reference gsiIconGroupRef(&sid->GsiGroupIcon, GsiGroupIcon.NameID());
		ovl.AddString(GsiGroupIcon.NameID(), nullptr);
		gsiIconGroupRef.AssignOwner(info);
		ovl.AddReference(gsiIconGroupRef, UNIQUE);
	}

	if (TxtGroupName.NameID().length())
	{
		Reference txtNameGroupRef(&sid->TxtGroupName, TxtGroupName.NameID());
		ovl.AddString(TxtGroupName.NameID(), nullptr);
		txtNameGroupRef.AssignOwner(info);
		ovl.AddReference(txtNameGroupRef, UNIQUE);
	}

	sid->SvdCount = Svds.size();
	sid->Svds = reinterpret_cast<SvdPtr*>(unique);
	ovl.AddPointer(Ptr(sid->Svds));
	unique += Svds.size() * sizeof(SvdPtr);

	for (int i = 0; i < Svds.size(); i++)
	{
		Reference svdRef(&sid->Svds[i], Svds[i].NameID());
		ovl.AddString(Svds[i].NameID(), nullptr);
		svdRef.AssignOwner(info);
		ovl.AddReference(svdRef, UNIQUE);
	}

	sid->Unknown01 = Unknown01;
	sid->Flags = Flags;
	sid->PositioningType = PositioningType;
	sid->AddonPack = AddonPack;
	sid->Unknown02 = Unknown02;
	sid->XSquareCount = XSquareCount;
	sid->ZSquareCount = ZSquareCount;
	sid->Position = Position;
	sid->Size = Size;
	sid->Cost = Cost;
	sid->Refund = Refund;
	sid->Unknown03 = Unknown03;
	sid->SceneryItemType = SceneryItemType;
	sid->Unknown04 = Unknown04;
	sid->Unknown05 = Unknown05;
	sid->StallUnknown01 = StallUnknown01;
	sid->StallUnknown02 = StallUnknown02;
	sid->DefaultColors = DefaultColors;
	sid->Unknown06 = Unknown06;
	sid->Unknown07 = Unknown07;
	sid->Unknown08 = Unknown08;
	sid->Unknown09 = Unknown09;
	sid->Unknown10 = Unknown10;
	sid->Unknown11 = Unknown11;
	sid->Unknown12 = Unknown12;
	sid->Unknown13 = Unknown13;
	sid->Unknown14 = Unknown14;
	sid->OvlPath = nullptr;
	sid->Supports = nullptr;

	if (Supports.length())
	{
		ovl.AddString(Supports, &sid->Supports);
		ovl.AddPointer(Ptr(sid->Supports));
	}

	ovl.AddString(OvlPath, &sid->OvlPath);
	ovl.AddPointer(Ptr(sid->OvlPath));

	sid->PositionData = reinterpret_cast<PositioningRawData*>(common);
	ovl.AddPointer(Ptr(sid->PositionData));
	common += XSquareCount * ZSquareCount * sizeof(PositioningRawData);

	if (PositioningData.size())
	{
		for (int i = 0; i < XSquareCount * ZSquareCount; i++)
		{
			if (PositioningData.size() >= (XSquareCount * ZSquareCount))
			{
				if (PositioningData[i].ActualHeight())
				{
					sid->PositionData[i].Data = reinterpret_cast<unsigned int*>(common);
					common += PositioningData[i].DataSize();
					PositioningData[i].CopyDataTo(ovl, &sid->PositionData[i], sid->PositionData[i].Data);
				}
			}
			else
			{
				if (PositioningData[0].ActualHeight())
				{
					sid->PositionData[0].Data = reinterpret_cast<unsigned int*>(common);
					common += PositioningData[0].DataSize();
					PositioningData[0].CopyDataTo(ovl, &sid->PositionData[0], sid->PositionData[0].Data);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < XSquareCount * ZSquareCount; i++)
		{
			PositionData data;
			data.CopyDataTo(ovl, &sid->PositionData[i], nullptr);
		}
	}

	if (Parameters.size())
	{
		sid->Parameters = reinterpret_cast<ParameterRawData*>(common);
		sid->ParameterCount = Parameters.size();
		ovl.AddPointer(Ptr(sid->Parameters));
		common += Parameters.size() * sizeof(ParameterRawData);

		for (int i = 0; i < Parameters.size(); i++)
		{
			ovl.AddString(Parameters[i].Type, &sid->Parameters[i].Type);
			ovl.AddPointer(Ptr(Parameters[i].Type));
			ovl.AddString(Parameters[i].Parameters, &sid->Parameters[i].Parameters);
			ovl.AddPointer(Ptr(Parameters[i].Parameters));
		}
	}

	ovl.AddIdentifier(id, UNIQUE);
	ovl.AddDataInfo(info, UNIQUE);
	ovl.AddReference(txtNameRef, UNIQUE);
	ovl.AddReference(gsiIconRef, UNIQUE);

	ovl.GetLog().Info("SceneryItem::CopyDataTo(..): Created SceneryItem \"" + _name + "\"");
}

StructureHeader SceneryItem::GetHeader()
{
	StructureHeader h;
	h.LoaderType = RCT3LOADER;
	h.StructName = "SceneryItem";
	h.StructID = "sid";
	h.TypeNumber = 1;
	return h;
}

void SceneryItemCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(SceneryItem::GetHeader());

	unsigned int uniqueSize = 0, commonSize = 0;

	for (auto s : _structs)
	{
		uniqueSize += s->GetDataSize(UNIQUE);
		commonSize += s->GetDataSize(COMMON);
	}

	DataEntry& uniqueEntry = ovl.CreateEntry(UNIQUE, 2, uniqueSize);
	DataEntry& commonEntry = ovl.CreateEntry(COMMON, 2, commonSize);

	unsigned char* uniqueData = uniqueEntry.Data;
	unsigned char* commonData = commonEntry.Data;

	for (auto s : _structs)
	{
		s->CopyDataTo(ovl, uniqueData, commonData, headerIndex);
		uniqueData += s->GetDataSize(UNIQUE);
		commonData += s->GetDataSize(COMMON);
	}
}