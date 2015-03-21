// PathRaw.h

#pragma once

#include "stdafx.hpp"
#include "TextString.hpp"
#include "GuiSkinItemRaw.hpp"
#include "OvlRaw.hpp"

namespace RCT3Asset
{

	struct Research
	{
		unsigned char* Category;
		unsigned int Unknown01;
		unsigned int Unknown02;
	};

	struct PathSectionRawData
	{
		union
		{
			OvlString Sections[4];

			struct
			{
				OvlString North;
				OvlString South;
				OvlString East;
				OvlString West;
			};
		};
	};

	struct PathFlags
	{
		enum
		{
			Default = 0x00000001,
			Underwater = 0x00000002,
			Extended = 0x01000000
		};
	};

	struct PathRawData
	{
		unsigned int Flags;
		OvlString Name;
		TxtPtr Text;
		GsiPtr Icon;
		OvlString TextureA;
		OvlString TextureB;
		PathSectionRawData Flat;
		PathSectionRawData StraightA;
		PathSectionRawData StraightB;
		PathSectionRawData TurnU;
		PathSectionRawData TurnLA;
		PathSectionRawData TurnLB;
		PathSectionRawData TurnTA;
		PathSectionRawData TurnTB;
		PathSectionRawData TurnTC;
		PathSectionRawData TurnX;
		PathSectionRawData CornerA;
		PathSectionRawData CornerB;
		PathSectionRawData CornerC;
		PathSectionRawData CornerD;
		PathSectionRawData Slope;
		PathSectionRawData SlopeStraight;
		PathSectionRawData SlopeStraightLeft;
		PathSectionRawData SlopeStraightRight;
		PathSectionRawData SlopeMid;
		unsigned int ResearchCategoryCount;
		Research* ResearchCategories;
	};

	struct PathExtendedRawData
	{
		unsigned int Flags;
		OvlString Name;
		TxtPtr Text;
		GsiPtr Icon;
		OvlString TextureA;
		OvlString TextureB;
		PathSectionRawData Flat;
		PathSectionRawData StraightA;
		PathSectionRawData StraightB;
		PathSectionRawData TurnU;
		PathSectionRawData TurnLA;
		PathSectionRawData TurnLB;
		PathSectionRawData TurnTA;
		PathSectionRawData TurnTB;
		PathSectionRawData TurnTC;
		PathSectionRawData TurnX;
		PathSectionRawData CornerA;
		PathSectionRawData CornerB;
		PathSectionRawData CornerC;
		PathSectionRawData CornerD;
		PathSectionRawData Slope;
		PathSectionRawData SlopeStraight;
		PathSectionRawData SlopeStraightLeft;
		PathSectionRawData SlopeStraightRight;
		PathSectionRawData SlopeMid;
		unsigned int ResearchCategoryCount;
		Research* ResearchCategories;

		unsigned int Unknown01;
		unsigned int Unknown02;
		PathSectionRawData FlatFC;
		PathSectionRawData SlopeFC;
		PathSectionRawData SlopeBC;
		PathSectionRawData SlopeTC;
		PathSectionRawData SlopeStraightFC;
		PathSectionRawData SlopeStraightBC;
		PathSectionRawData SlopeStraightTC;
		PathSectionRawData SlopeStraightLeftFC;
		PathSectionRawData SlopeStraightLeftBC;
		PathSectionRawData SlopeStraightLeftTC;
		PathSectionRawData SlopeStraightRightFC;
		PathSectionRawData SlopeStraightRightBC;
		PathSectionRawData SlopeStraightRightTC;
		PathSectionRawData SlopeMidFC;
		PathSectionRawData SlopeMidBC;
		PathSectionRawData SlopeMidTC;
		OvlString Paving;
	};
}