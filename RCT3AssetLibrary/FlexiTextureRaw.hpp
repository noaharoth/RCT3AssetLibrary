// FlexiTextureRaw.hpp

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