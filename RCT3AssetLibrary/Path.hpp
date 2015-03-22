// Path.hpp

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
#include "PathRaw.hpp"
#include "StructRef.hpp"
#include "TextString.hpp"
#include "GuiSkinItem.hpp"
#include "StructureCollection.hpp"

namespace RCT3Asset
{

	class PathSection
	{
	private:
		std::string _sections[4];

	public:

		PathSection& operator=(const std::string section);

		std::string& operator[](unsigned int index);

	};

	class Path
	{
	private:
		std::string _name;

		inline void _copySection(OvlFile& ovl, PathSection& section, PathSectionRawData& data);

		inline void _copySectionOptional(OvlFile& ovl, PathSection& section, PathSectionRawData& data);

	public:
		StructRef<TextString> Text;
		StructRef<GuiSkinItem> GsiIcon;
		std::string TextureA; // TextureA and TextureB are not StructRef's for some reason
		std::string TextureB;
		PathSection Flat;
		PathSection StraightA;
		PathSection StraightB;
		PathSection TurnU;
		PathSection TurnLA;
		PathSection TurnLB;
		PathSection TurnTA;
		PathSection TurnTB;
		PathSection TurnTC;
		PathSection TurnX;
		PathSection CornerA;
		PathSection CornerB;
		PathSection CornerC;
		PathSection CornerD;
		PathSection Slope;
		PathSection SlopeStraight;
		PathSection SlopeStraightLeft;
		PathSection SlopeStraightRight;
		PathSection SlopeMid;
		std::vector<Research> ResearchCategories; // not quite sure what these are...
		unsigned int Flags;

//#pragma region Extended

		unsigned int Unknown01;
		unsigned int Unknown02;
		PathSection FlatFC;
		PathSection SlopeFC;
		PathSection SlopeBC;
		PathSection SlopeTC;
		PathSection SlopeStraightFC;
		PathSection SlopeStraightBC;
		PathSection SlopeStraightTC;
		PathSection SlopeStraightLeftFC;
		PathSection SlopeStraightLeftBC;
		PathSection SlopeStraightLeftTC;
		PathSection SlopeStraightRightFC;
		PathSection SlopeStraightRightBC;
		PathSection SlopeStraightRightTC;
		PathSection SlopeMidFC;
		PathSection SlopeMidBC;
		PathSection SlopeMidTC;
		std::string Paving;

//#pragma endregion

		Path();

		unsigned int DataSize(unsigned int file);

		std::string Name() const;

		void Name(std::string name);

		void SetUnderwaterFlag();

		void SetExtendedFlag();

		bool IsExtended() const;

		std::string GetNameID() const;

		void CopyDataTo(OvlFile& ovl, void* raw, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};

	class PathCollection final : public StructureCollection < Path >
	{
	public:

		void AddTo(OvlFile& ovl);

	};

}