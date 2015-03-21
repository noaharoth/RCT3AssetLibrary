// FlicManager.cpp

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

	DataEntry& entry = ovl.CreateEntry(COMMON, 2, GetDataSize());

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
		ExtraData extra = ovl.CreateAndAddExtraData(extraDataSize, COMMON);

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

			mip->Blocks = _textures[i]->Mips[j].GetImage().Blocks();
			mip->Pitch = _textures[i]->Mips[j].GetImage().Pitch();
			mip->Height = _textures[i]->Mips[j].GetImage().Dimension();
			mip->Width = _textures[i]->Mips[j].GetImage().Dimension();

			_textures[i]->Mips[j].GetImage().CopyDataTo(extraData);
			extraData += _textures[i]->Mips[j].GetImage().GetDataSize();
		}

		ovl.AddDataInfo(info, COMMON);

		ovl.GetLog().Info("FlicManager::CreateAndAssign(..): Created & assigned Flic data.");
	}
}

StructureHeader FlicManager::GetHeader()
{
	StructureHeader h;
	h.LoaderType = FDGKLOADER;
	h.StructName = "Flic";
	h.StructID = "flic";
	h.TypeNumber = 2;
	return h;
}