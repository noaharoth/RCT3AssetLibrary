// GuiSkinItemRaw.h

#pragma once

#include "stdafx.hpp"
#include "Texture.hpp"

namespace RCT3Asset
{

	struct IconPosition
	{
		unsigned int Left;
		unsigned int Top;
		unsigned int Right;
		unsigned int Bottom;
	};

	struct GuiSkinItemRawData
	{
		unsigned int GsiType;
		TexPtr Texture;
		IconPosition* PositioningData;
		unsigned int Unknown;
	};

	typedef GuiSkinItemRawData* GsiPtr;

}