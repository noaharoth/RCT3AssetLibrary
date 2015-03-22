// FtxImage.cpp

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
#include "FtxImage.hpp"

using namespace RCT3Asset;

bool FtxImage::_rgbPaletteMade = false;

BGRAColor FtxImage::_rgbPalette[256];

FtxImage::FtxImage(RCT3Debugging::OutputLog& log)
	: OvlImage(log)
{

}

FtxImage::FtxImage(const std::string& imageFile, RCT3Debugging::OutputLog& log)
	: OvlImage(imageFile, log)
{

}

unsigned int FtxImage::GetIndexedDataSize() const
{
	return Dimension() * Dimension();
}

unsigned int FtxImage::GetAlphaDataSize() const
{
	if (HasAlpha())
		return Dimension();

	return 0;
}

unsigned int FtxImage::GetPaletteDataSize() const
{
	return sizeof(BGRAColor) * 256;
}

void FtxImage::CopyDataTo(unsigned char* textureDest, unsigned char* paletteDest, unsigned char* alphaDest, bool makeRecolorable)
{
	if (!_isValid)
	{
		_log.Error("FtxImage::CopyDataTo(...): Tried to access invalid image");
		return;
	}

	try
	{
		Magick::Image temp = _image;

		temp.flip();

		BGRAColor* palette = reinterpret_cast<BGRAColor*>(paletteDest);

		if (makeRecolorable && (temp.type() != Magick::PaletteType))
		{
			memcpy(paletteDest, GetRGBPalette(), sizeof(_rgbPalette));

			const Magick::PixelPacket* src = temp.getConstPixels(0, 0, temp.columns(), temp.rows());

			unsigned int distance, max;
			int r, d1, d2, d3;
			unsigned int p;

			for (r = 0; r < temp.columns() * temp.rows(); ++r)
			{
				max = UINT_MAX;
				for (p = 1; p < 256; p++)
				{
					d1 = static_cast<int>(src[r].red) - static_cast<int>(palette[p].R);
					d2 = static_cast<int>(src[r].green) - static_cast<int>(palette[p].G);
					d3 = static_cast<int>(src[r].blue) - static_cast<int>(palette[p].B);
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
			temp.matte(false);

			if ((temp.type() != Magick::PaletteType) || (temp.totalColors() != 256))
			{
				temp.quantizeColors(256);
				temp.quantizeDither(false);
				temp.quantize();
				temp.type(Magick::PaletteType);
			}

			for (unsigned int i = 0; i < temp.colorMapSize(); ++i)
			{
				Magick::Color col = temp.colorMap(i);
				palette[i].R = col.redQuantum();
				palette[i].G = col.greenQuantum();
				palette[i].B = col.blueQuantum();
			}

			temp.getConstPixels(0, 0, temp.columns(), temp.rows());
			const Magick::IndexPacket* indices = temp.getConstIndexes();
			memcpy(textureDest, indices, temp.columns() * temp.rows());
		}

		if (alphaDest != nullptr && HasAlpha())
		{
			_image.write(0, 0, _image.columns(), _image.rows(), "A", Magick::CharPixel, alphaDest);
			for (unsigned int i = 0; i < _image.columns() * _image.rows(); ++i)
				alphaDest[i] = 255 - alphaDest[i];
		}
	}
	catch (std::exception& e)
	{
		_log.Error("GraphicsMagick threw an exception: " + std::string(e.what()));
	}
}

const BGRAColor* FtxImage::GetRGBPalette()
{
	if (_rgbPaletteMade)
		return _rgbPalette;

	for (int i = 1; i <= 85; i++)
	{
		_rgbPalette[i].R = ((86 - i) * 255) / 85;
		_rgbPalette[i + 85].G = ((86 - i) * 255) / 85;
		_rgbPalette[i + 170].B = ((86 - i) * 255) / 85;
	}

	_rgbPaletteMade = true;

	return _rgbPalette;
}