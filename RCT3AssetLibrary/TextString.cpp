// TextString.cpp

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

#include "stdafx.hpp"
#include "TextString.hpp"

using namespace RCT3Asset;

TextString::TextString() 
{

}

TextString::TextString(std::string name, std::wstring text) : _text(text), _name(name)
{ 

}

unsigned int TextString::DataSize(unsigned int file)
{
	return (_text.length() + 1) * sizeof(TextStringRawData);
}

unsigned int TextString::Length() const
{
	return _text.length();
}

std::string TextString::GetNameID() const
{
	return _name + ":txt";
}

std::string TextString::Name() const
{
	return _name;
}

void TextString::Name(std::string name)
{
	_name = name;
}

std::wstring TextString::Text() const
{
	return _text;
}

void TextString::Text(std::wstring text)
{
	_text = text;
}

void TextString::CopyDataTo(OvlFile& ovl, TextStringRawData* data, unsigned int headerIndex)
{
	wcscpy(data, _text.c_str());

	std::string nameID = GetNameID();

	Identifier id(nameID);
	ovl.AddString(nameID, nullptr);
	id.AssignData(data);
	ovl.AddIdentifier(id, COMMON);

	DataInfo info(headerIndex, data, id, 0);
	ovl.AddDataInfo(info, COMMON);

	ovl.GetLog().Info("TextString::CopyDataTo(..): Created TextString \"" + _name + "\"");
}

StructureHeader TextString::GetHeader()
{
	StructureHeader txtHeader;
	txtHeader.LoaderType = FDGKLOADER;
	txtHeader.TypeNumber = 2;
	txtHeader.StructID = "txt";
	txtHeader.StructName = "Text";
	return txtHeader;
}

// ------------------------------------------------- //

void TextStringCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(TextString::GetHeader());

	unsigned int entrySize = 0;

	for (auto t : _structs)
	{
		entrySize += t->DataSize(COMMON);
	}

	DataEntry& entry = ovl.CreateEntry(COMMON, 2, entrySize);
	TextStringRawData* raw = reinterpret_cast<TextStringRawData*>(entry.Data);

	for (auto t : _structs)
	{
		t->CopyDataTo(ovl, raw, headerIndex);

		raw += t->Length() + 1; // + 1 for the null terminator
	}
}