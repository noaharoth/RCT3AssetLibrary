// FtxImage.hpp

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
#include "OvlImage.hpp"
#include "Vertex.hpp"

namespace RCT3Asset
{

	// FtxImage's use an indexed image format.
	class R3AL_API FtxImage final : public OvlImage
	{
	private:
		static BGRAColor _rgbPalette[256];
		static bool _rgbPaletteMade;

	public:

		FtxImage(RCT3Debugging::OutputLog& log);

		FtxImage(const std::string& imageFile, RCT3Debugging::OutputLog& log);

		inline unsigned int GetIndexedDataSize() const;

		inline unsigned int GetAlphaDataSize() const;

		inline unsigned int GetPaletteDataSize() const;

		void CopyDataTo(unsigned char* textureDest, unsigned char* paletteDest,
			unsigned char* alphaDest, bool makeRecolorable = false);

		static const BGRAColor* GetRGBPalette();

	};

}