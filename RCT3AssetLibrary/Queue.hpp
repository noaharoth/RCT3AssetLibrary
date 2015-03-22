// Queue.hpp

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
#include "OvlFile.hpp"
#include "QueueRaw.hpp"
#include "TextString.hpp"
#include "GuiSkinItem.hpp"
#include "FlexiTexture.hpp"
#include "StructRef.hpp"
#include "StructureCollection.hpp"

namespace RCT3Asset
{
	
	class Queue
	{
	private:
		std::string _name;

	public:
		StructRef<TextString> Text;
		StructRef<GuiSkinItem> GsiIcon;
		StructRef<FlexiTexture> FtxTexture;
		std::string Straight;
		std::string TurnL;
		std::string TurnR;
		std::string SlopeUp;
		std::string SlopeDown;
		std::string SlopeStraight1;
		std::string SlopeStraight2;

		Queue();

		void Name(std::string name);

		std::string Name() const;

		std::string GetNameID() const;

		unsigned int DataSize(unsigned int file);

		void CopyDataTo(OvlFile& ovl, QueueRawData* queue, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};


	class QueueCollection final : public StructureCollection < Queue >
	{
	public:

		void AddTo(OvlFile& ovl);

	};

}