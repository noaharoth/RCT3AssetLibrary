// TextString.hpp

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
#include "StructureCollection.hpp"

namespace RCT3Asset
{
	typedef wchar_t TextStringRawData;
	typedef wchar_t* TxtRef;

	class TextString
	{
	private:
		std::wstring _text;
		std::string _name;
	public:

		TextString();

		TextString(std::string name, std::wstring text);

		unsigned int DataSize(unsigned int file);

		unsigned int Length() const;

		std::string GetNameID() const;

		std::string Name() const;

		void Name(std::string name);

		std::wstring Text() const;

		void Text(std::wstring text);

		void CopyDataTo(OvlFile& ovl, TextStringRawData* data, unsigned int headerIndex);

		static StructureHeader GetHeader();
	};

	class TextStringCollection final : public StructureCollection < TextString >
	{
	public:

		void AddTo(OvlFile& ovl);

	};
}