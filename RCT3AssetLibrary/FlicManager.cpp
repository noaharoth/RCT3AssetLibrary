// FlicManager.cpp

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
#include "FlicManager.hpp"

using namespace RCT3Asset;

void FlicManager::Add(Texture& tex)
{
	_textures.push_back(&tex);
}

unsigned int FlicManager::GetDataSize()
{
	return _textures.size() * sizeof(FlicRawData);
}

void FlicManager::CreateAndAssign(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(GetHeader());

	DataEntry& entry = ovl.CreateEntry(OvlType::Common, 2, GetDataSize());

	FlicRawData* raw = reinterpret_cast<FlicRawData*>(entry.Data);

	for (int i = 0; i < _textures.size(); i++)
	{
		raw[i].FlicInfoPtr = &raw[i].FlicInfo;
		ovl.AddPointer(Ptr(raw[i].FlicInfoPtr));

		raw[i].FlicInfo.FlicDataPtr = nullptr;
		raw[i].FlicInfo.Unknown01 = _textures[i]->FlicUnknown01;
		raw[i].FlicInfo.Unknown02 = _textures[i]->FlicUnknown02;

		_textures[i]->FlicAssign(&raw[i].FlicInfo);

		//ovl.GetLog().Debug("FLIC: ptrToFlicInfo = " + STR((unsigned int)&raw[i].FlicInfo));

		_textures[i]->FlicAssign(&raw[i].FlicInfoPtr);

		//ovl.GetLog().Debug("FLIC: ptrToFlicInfoPtr = " + STR((unsigned int)&raw[i].FlicInfoPtr));

		_textures[i]->FlicMade(true);

		DataInfo info(headerIndex, &raw[i].FlicInfo, 0);

		// extra data

		unsigned int extraDataSize = sizeof(FlicHeader) + _textures[i]->MipDataSize() + _textures[i]->ImageDataSize();
		ExtraData extra = ovl.CreateAndAddExtraData(extraDataSize, OvlType::Common);

		info.ExtraData.push_back(extra);

		unsigned char* extraData = extra.Data;

		FlicHeader* flicHeader = reinterpret_cast<FlicHeader*>(extraData);
		extraData += sizeof(FlicHeader);

		flicHeader->Format = _textures[i]->Mips[0].GetImage().GetFlicFormat();
		flicHeader->Height = _textures[i]->Dimension();
		flicHeader->Width = _textures[i]->Dimension();
		flicHeader->MipCount = _textures[i]->Mips.size();

		// mips

		MipHeader* mip;
		for (int j = 0; j < _textures[i]->Mips.size(); j++)
		{
			mip = reinterpret_cast<MipHeader*>(extraData);
			extraData += sizeof(MipHeader);

			TexImage& image = _textures[i]->Mips[j].GetImage();

			mip->Blocks = image.Blocks();
			mip->Pitch = image.Pitch();
			mip->Height = image.Dimension();
			mip->Width = image.Dimension();

			image.CopyDataTo(extraData);
			extraData += image.GetDataSize();
		}

		ovl.AddDataInfo(info, OvlType::Common);

		ovl.GetLog().Info("FlicManager::CreateAndAssign(..): Created & assigned Flic data.");
	}
}

StructureHeader FlicManager::GetHeader()
{
	StructureHeader h;
	h.LoaderType = OvlLoaderType::FDGK;
	h.StructName = "Flic";
	h.StructID = "flic";
	h.TypeNumber = 2;
	return h;
}