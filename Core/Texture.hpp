// Texture.hpp

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
#include "TextureRaw.hpp"
#include "OvlFile.hpp"
#include "TexImage.hpp"
#include "TextureStyle.hpp"
#include "StructureCollection.hpp"

namespace RCT3Asset
{

	class R3AL_API TextureMip
	{
		TexImage& _image;
	public:

		TextureMip(TexImage& image);

		void CopyDataTo(MipHeader* data);

		void SetImage(TexImage image);

		TexImage& GetImage();

	};

	class R3AL_API Texture
	{
	private:
		FlicInfoData** _ptrToFlicInfoPtr;
		FlicInfoData* _ptrToFlicInfo;
		std::string _name;
		bool _flicMade;

	public:
		std::vector<TextureMip> Mips;
		TextureStyle TxsStyle; // ref
		unsigned int Unknown01; // unknown 1-8 is always 0x70007
		unsigned int Unknown02;
		unsigned int Unknown03;
		unsigned int Unknown04;
		unsigned int Unknown05;
		unsigned int Unknown06;
		unsigned int Unknown07;
		unsigned int Unknown08;
		unsigned int Unknown09; // usually 1
		unsigned int Unknown10; // usually 8. 4 if unknown 9 and 12 are 0, 12 if they are both 2
		unsigned int Unknown11; // usually 0x10
		unsigned int Unknown12;

		unsigned int FlicUnknown01;
		float FlicUnknown02;

		Texture();

		void Name(std::string name);

		std::string Name() const;

		std::string GetNameID() const;

		unsigned int Dimension();

		void FlicAssign(FlicInfoData** ptr);

		void FlicAssign(FlicInfoData* ptr);

		bool FlicMade() const;

		void FlicMade(bool made);

		unsigned int DataSize(unsigned int file) const;

		unsigned int MipDataSize() const;

		unsigned int ImageDataSize();

		void CopyDataTo(OvlFile& ovl, TextureRawData* data, unsigned int headerIndex);

		static StructureHeader GetHeader();
	};

	class R3AL_API TextureCollection final : public StructureCollection < Texture >
	{
	public:

		void AddTo(OvlFile& ovl);

	};
}