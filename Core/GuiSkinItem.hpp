// GuiSkinItem.hpp

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
#include "GuiSkinItemRaw.hpp"
#include "Texture.hpp"
#include "StructureCollection.hpp"
#include "StructRef.hpp"
#include "OvlFile.hpp"

namespace RCT3Asset
{

	class R3AL_API GuiSkinItem
	{
	private:
		std::string _name;
	public:
		IconPosition Position;
		StructRef<Texture> Texture;
		unsigned int GsiType;
		unsigned int Unknown;

		GuiSkinItem();

		void Name(std::string name);

		std::string Name() const;

		std::string GetNameID() const;

		unsigned int GetDataSize(unsigned int file);

		void CopyDataTo(OvlFile& ovl, GuiSkinItemRawData* gsi, IconPosition* pos, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};


	class R3AL_API GuiSkinItemCollection final : public StructureCollection < GuiSkinItem >
	{
	public:

		void AddTo(OvlFile& ovl);

	};

}