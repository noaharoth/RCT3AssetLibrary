// FlicRaw.hpp

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

	struct FlicInfoData
	{
		unsigned int* FlicDataPtr;
		unsigned int Unknown01; // 1
		float Unknown02; // 1.0
	};

	struct FlicRawData
	{
		FlicInfoData* FlicInfoPtr; // points to following FlicInfoData (?)
		FlicInfoData FlicInfo;
	};

	struct FlicHeader
	{
		unsigned int Format;
		unsigned int Width;
		unsigned int Height;
		unsigned int MipCount;
	};

	struct MipHeader
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Pitch;
		unsigned int Blocks;
	};

}