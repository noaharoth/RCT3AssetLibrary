// TextureStyle.cpp

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
#include "TextureStyle.hpp"

using namespace RCT3Asset;

TextureStyle::TextureStyle() 
{ 

}

TextureStyle::TextureStyle(std::string style) : _style(style) 
{ 

}

std::string TextureStyle::GetStyle() const
{
	return _style;
}

std::string TextureStyle::GetNameID() const
{
	return _style + ":txs";
}

TextureStyle& TextureStyle::operator=(const std::string& value)
{
	_style = value;
	return *this;
}

void TextureStyle::AddTo(OvlFile& ovl)
{
	ovl.AddString(GetNameID(), nullptr);

	ovl.GetLog().Info("TextureStyle::AddTo(..): Added TextureStyle \"" + _style + "\"");
}

const TextureStyle TextureStyle::PathGround = TextureStyle("PathGround");
const TextureStyle TextureStyle::GUIIcon = TextureStyle("GUIIcon");