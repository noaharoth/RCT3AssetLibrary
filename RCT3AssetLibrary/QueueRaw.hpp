// QueueRaw.h

#pragma once

#include "stdafx.hpp"
#include "OvlRaw.hpp"
#include "TextString.hpp"
#include "GuiSkinItemRaw.hpp"
#include "PathRaw.hpp"
#include "FlexiTextureRaw.hpp"

namespace RCT3Asset
{

	struct QueueRawData
	{
		OvlString Name;
		TxtPtr Text;
		GsiPtr Icon;
		FtxPtr Texture;
		OvlString Straight;
		OvlString TurnL;
		OvlString TurnR;
		OvlString SlopeUp;
		OvlString SlopeDown;
		OvlString SlopeStraight1;
		OvlString SlopeStraight2;
		unsigned int ResearchCategoryCount;
		Research* ResearchCategories;
	};

}