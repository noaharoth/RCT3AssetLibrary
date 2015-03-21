// FlicRaw.h

#pragma once

#include "stdafx.hpp"

namespace RCT3Asset
{

	struct FlicInfoData
	{
		unsigned int* FlicDataPtr;
		unsigned int Unknown01; // 1
		float Unknown02; // 1.0
	};

	struct FlicRawData
	{
		FlicInfoData* FlicInfoPtr; // points to following FlicInfoData (?)
		FlicInfoData FlicInfo;
	};

	struct FlicHeader
	{
		unsigned int Format;
		unsigned int Width;
		unsigned int Height;
		unsigned int MipCount;
	};

	struct MipHeader
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Pitch;
		unsigned int Blocks;
	};

}