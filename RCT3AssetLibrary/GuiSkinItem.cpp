// GuiSkinItem.cpp

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
#include "GuiSkinItem.hpp"

using namespace RCT3Asset;

GuiSkinItem::GuiSkinItem() : GsiType(0), Unknown(0)
{

}

void GuiSkinItem::Name(std::string name)
{
	_name = name;
}

std::string GuiSkinItem::Name() const
{
	return _name;
}

std::string GuiSkinItem::GetNameID() const
{
	return _name + ":gsi";
}

unsigned int GuiSkinItem::GetDataSize(unsigned int file)
{
	if (file == COMMON)
	{
		return sizeof(IconPosition);
	}

	return sizeof(GuiSkinItemRawData);
}

void GuiSkinItem::CopyDataTo(OvlFile& ovl, GuiSkinItemRawData* gsi, IconPosition* pos, unsigned int headerIndex)
{
	ovl.AddString(GetNameID(), nullptr);

	gsi->GsiType = GsiType;
	gsi->Unknown = Unknown;

	gsi->PositioningData = pos;
	ovl.AddPointer(Ptr(gsi->PositioningData));

	*pos = Position;

	Identifier id(GetNameID());
	id.AssignData(gsi);

	DataInfo info(headerIndex, gsi, 1);

	Reference texRef(&gsi->Texture, Texture.NameID());

	texRef.AssignOwner(info);

	ovl.AddIdentifier(id, UNIQUE);
	ovl.AddDataInfo(info, UNIQUE);
	ovl.AddReference(texRef, UNIQUE);

	ovl.GetLog().Info("GuiSkinItem::CopyDataTo(..): Created GuiSkinItem \"" + _name + "\"");
}

StructureHeader GuiSkinItem::GetHeader()
{
	StructureHeader h;
	h.TypeNumber = 1;
	h.StructID = "gsi";
	h.StructName = "GUISkinItem";
	h.LoaderType = FDGKLOADER;
	return h;
}

void GuiSkinItemCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(GuiSkinItem::GetHeader());

	unsigned int uniqueSize = 0, commonSize = 0;

	for (auto g : _structs)
	{
		uniqueSize += g->GetDataSize(UNIQUE);
		commonSize += g->GetDataSize(COMMON);
	}

	DataEntry& uniqueEntry = ovl.CreateEntry(UNIQUE, 2, uniqueSize);
	DataEntry& commonEntry = ovl.CreateEntry(COMMON, 2, commonSize);

	GuiSkinItemRawData* gsi = reinterpret_cast<GuiSkinItemRawData*>(uniqueEntry.Data);
	IconPosition* pos = reinterpret_cast<IconPosition*>(commonEntry.Data);

	for (int i = 0; i < _structs.size(); i++)
	{
		_structs[i]->CopyDataTo(ovl, &gsi[i], &pos[i], headerIndex);
	}
}