// FtxImage.hpp
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

#pragma once

#include "stdafx.hpp"
#include "OvlImage.hpp"

namespace RCT3Asset
{

	class FtxImage : public OvlImage
	{
	private:
		static BGRAColor _recolorPalette[256];

		bool _recolorable;

	public:

		FtxImage(RCT3Debugging::OutputLog& log);

		FtxImage(RCT3Debugging::OutputLog& log, const std::string& fileName, bool recolorable);

		unsigned int GetIndexedDataSize() const;

		unsigned int GetAlphaDataSize() const;

		unsigned int GetPaletteDataSize() const;

		void CopyDataTo(unsigned char* textureDest, unsigned char* paletteDest, unsigned char* alphaDest);

	};

}