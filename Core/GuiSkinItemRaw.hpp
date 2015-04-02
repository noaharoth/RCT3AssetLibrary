// GuiSkinItemRaw.hpp

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