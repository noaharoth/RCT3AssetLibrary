// QueueRaw.hpp

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