// FtxImage.cpp
// No longer using GraphicsMagick and libsquish, instead using ResIL

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
*/

#include "stdafx.hpp"
#include "FtxImage.hpp"

using namespace RCT3Asset;

FtxImage::FtxImage(RCT3Debugging::OutputLog& log) : OvlImage(log), _recolorable(false)
{

}

FtxImage::FtxImage(RCT3Debugging::OutputLog& log, const std::string& fileName, bool recolorable) : OvlImage(log, fileName), _recolorable(recolorable)
{
	if (!_image)
		return;

	ILint origin;

	il2GetImageInteger(_image, IL_IMAGE_ORIGIN, &origin);

	if (origin == IL_ORIGIN_UPPER_LEFT)
	{
		if (!ilu2FlipImage(_image))
		{
			_log.Error("FtxImage::FtxImage(..): Unable to flip image.");
			return;
		}
	}
}

unsigned int FtxImage::GetIndexedDataSize() const
{
	return Dimension() * Dimension();
}

unsigned int FtxImage::GetAlphaDataSize() const
{
	return Dimension();
}

unsigned int FtxImage::GetPaletteDataSize() const
{
	return 256;
}

void FtxImage::CopyDataTo(unsigned char* textureDest, unsigned char* paletteDest, unsigned char* alphaDest)
{
	ILubyte* data = il2GetData(_image);
	BGRAColor* pal = reinterpret_cast<BGRAColor*>(paletteDest);

	// Start with alpha channel

	if (alphaDest != nullptr && HasAlpha())
	{
		ilu2InvertAlpha(_image);
		memcpy(alphaDest, il2GetAlpha(_image, IL_UNSIGNED_BYTE), Dimension() * Dimension());
	}

	if (_recolorable)
	{
		memcpy(paletteDest, _recolorPalette, sizeof(_recolorPalette));

		if (HasAlpha())
		{

			RGBAColor* src = reinterpret_cast<RGBAColor*>(il2GetData(_image));

			unsigned int distance, max;
			int r, d1, d2, d3;
			unsigned int p;

			for (r = 0; r < Dimension() * Dimension(); ++r) // this might be wrong
			{
				max = UINT_MAX;
				for (p = 1; p < 256; p++)
				{
					d1 = static_cast<int>(src[r].R) - static_cast<int>(pal[p].R);
					d2 = static_cast<int>(src[r].G) - static_cast<int>(pal[p].G);
					d3 = static_cast<int>(src[r].B) - static_cast<int>(pal[p].B);
					distance = d1 * d1 + d2 * d2 + d3 * d3;
					if (distance < max)
					{
						max = distance;
						textureDest[r] = p;
					}
				}
			}
		}
		else
		{
			RGBColor* src = reinterpret_cast<RGBColor*>(il2GetData(_image));

			unsigned int distance, max;
			int r, d1, d2, d3;
			unsigned int p;

			for (r = 0; r < Dimension() * Dimension(); ++r) // this might be wrong
			{
				max = UINT_MAX;
				for (p = 1; p < 256; p++)
				{
					d1 = static_cast<int>(src[r].R) - static_cast<int>(pal[p].R);
					d2 = static_cast<int>(src[r].G) - static_cast<int>(pal[p].G);
					d3 = static_cast<int>(src[r].B) - static_cast<int>(pal[p].B);
					distance = d1 * d1 + d2 * d2 + d3 * d3;
					if (distance < max)
					{
						max = distance;
						textureDest[r] = p;
					}
				}
			}
		}
	}
	else
	{
		//il2SetInteger(IL_QUANTIZATION_MODE, IL_NEU_QUANT);
		il2SetInteger(IL_MAX_QUANT_INDICES, 256);
		//il2SetInteger(IL_NEU_QUANT_SAMPLE, 30);
		if (!il2ConvertImage(_image, IL_COLOR_INDEX, IL_UNSIGNED_BYTE))
		{
			_log.Error("FtxImage::FtxImage(..): Unable to convert image to color index format.");
			return;
		}

		memcpy(textureDest, il2GetData(_image), Dimension() * Dimension());

		RGBAColor* imagePal = reinterpret_cast<RGBAColor*>(il2GetPalette(_image));

		if (imagePal == nullptr)
		{
			_log.Error("FtxImage::FtxImage(..): Palette ptr returned by il2GetPalette(..) is null");
			return;
		}

		for (int i = 0; i < 256; i++)
		{
			pal[i].B = imagePal[i].B;
			pal[i].G = imagePal[i].G;
			pal[i].R = imagePal[i].R;
			pal[i].A = imagePal[i].A;
		}
	}
}