// FlexiTextureRaw.h

#pragma once

#include "stdafx.hpp"

namespace RCT3Asset
{

	// Note: The difference between Texture (tex) structures and FlexiTexture (ftx) structures is FTX can be recolorable.
	// Because of this, FTX texture data is not compressed via DXT compression. It is stored in 8bit format and the colors are
	// indexed. FTX textures can also be animated.



	struct FlexiTextureFrameRawData
	{
		unsigned int Scale;
		unsigned int Width;
		unsigned int Height;
		unsigned int Recolorability;
		unsigned char* PaletteData;
		unsigned char* TextureData;
		unsigned char* AlphaData;
	};

	struct FlexiTextureRawData
	{
		unsigned int Scale;
		unsigned int Width;
		unsigned int Height;
		unsigned int FramesPerSecond;
		unsigned int Recolorability;
		unsigned int FrameNumberCount;
		unsigned int* FrameNumbers;
		unsigned int FramesCount;
		FlexiTextureFrameRawData* Frames;
	};

	typedef FlexiTextureRawData* FtxPtr;
}