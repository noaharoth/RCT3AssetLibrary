// TextureStyle.cpp

#include "stdafx.hpp"
#include "TextureStyle.hpp"

using namespace RCT3Asset;

TextureStyle::TextureStyle() { }

TextureStyle::TextureStyle(std::string style) : _style(style) { }

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