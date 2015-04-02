// Texture.cpp

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
#include "Texture.hpp"

using namespace RCT3Asset;

TextureMip::TextureMip(TexImage& image)
	: _image(image)
{

}

void TextureMip::CopyDataTo(MipHeader* data)
{
	data->Height = _image.Dimension();
	data->Width = _image.Dimension();
	data->Blocks = _image.Blocks();
	data->Pitch = _image.Pitch();
}

TexImage& TextureMip::GetImage()
{
	return _image;
}

Texture::Texture()
{
	Unknown01 = 0x70007;
	Unknown02 = 0x70007;
	Unknown03 = 0x70007;
	Unknown04 = 0x70007;
	Unknown05 = 0x70007;
	Unknown06 = 0x70007;
	Unknown07 = 0x70007;
	Unknown08 = 0x70007;
	Unknown09 = 1;
	Unknown10 = 8;
	Unknown11 = 0x10;
	Unknown12 = 1;
	FlicUnknown01 = 1;
	FlicUnknown02 = 1.0f;
	_ptrToFlicInfo = nullptr;
	_ptrToFlicInfoPtr = nullptr;
	_flicMade = false;
}

void Texture::Name(std::string name)
{
	_name = name;
}

std::string Texture::Name() const
{
	return _name;
}

std::string Texture::GetNameID() const
{
	return _name + ":tex";
}

unsigned int Texture::Dimension()
{
	return Mips.begin()->GetImage().Dimension();
}

void Texture::FlicAssign(FlicInfoData** ptr)
{
	this->_ptrToFlicInfoPtr = ptr;
}

void Texture::FlicAssign(FlicInfoData* ptr)
{
	this->_ptrToFlicInfo = ptr;

}

bool Texture::FlicMade() const
{
	return _flicMade;
}

void Texture::FlicMade(bool made)
{
	_flicMade = made;
}

unsigned int Texture::DataSize(unsigned int file) const
{
	return sizeof(TextureRawData);
}

unsigned int Texture::MipDataSize() const
{
	return (Mips.size() + 1) * sizeof(MipHeader); // + 1 because there is a zeroed mipheader at the end
}

unsigned int Texture::ImageDataSize()
{
	unsigned int size = 0;
	for (unsigned int i = 0; i < Mips.size(); i++)
	{
		size += Mips[i].GetImage().GetDataSize();
	}

	return size;
}

void Texture::CopyDataTo(OvlFile& ovl, TextureRawData* data, unsigned int headerIndex)
{
	ovl.AddString(GetNameID(), nullptr);

	data->TexInfo.Unknown01 = Unknown01;
	data->TexInfo.Unknown02 = Unknown02;
	data->TexInfo.Unknown03 = Unknown03;
	data->TexInfo.Unknown04 = Unknown04;
	data->TexInfo.Unknown05 = Unknown05;
	data->TexInfo.Unknown06 = Unknown06;
	data->TexInfo.Unknown07 = Unknown07;
	data->TexInfo.Unknown08 = Unknown08;
	data->TexInfo.Unknown09 = Unknown09;
	data->TexInfo.Unknown10 = Unknown10;
	data->TexInfo.Unknown11 = Unknown11;
	data->TexInfo.Unknown12 = Unknown12;
	data->TexInfo.TxsRef = nullptr;

	if (!_flicMade)
	{
		ovl.GetLog().Error("Flic not made.");
		return;
	}

	// lots of weird pointer stuff here...
	data->TexInfo.PtrToFlicInfoPtr = _ptrToFlicInfoPtr;
	data->TexInfo.TexFlicPtr = &data->TexFlicPtr;
	data->TexFlicPtr.TexInfoPtr = &data->TexInfo;
	data->TexFlicPtr.FlicInfoPtr = _ptrToFlicInfo;

	ovl.AddPointer(Ptr(data->TexInfo.PtrToFlicInfoPtr));
	ovl.AddPointer(Ptr(data->TexInfo.TexFlicPtr));
	ovl.AddPointer(Ptr(data->TexFlicPtr.TexInfoPtr));
	ovl.AddPointer(Ptr(data->TexFlicPtr.FlicInfoPtr));

	Identifier id(GetNameID());
	id.AssignData(data);

	DataInfo info(headerIndex, data, id, 1);

	Reference txsRef(&data->TexInfo.TxsRef, TxsStyle.GetNameID());
	txsRef.AssignOwner(info);

	ovl.AddIdentifier(id, OvlType::Unique);
	ovl.AddDataInfo(info, OvlType::Unique);
	ovl.AddReference(txsRef, OvlType::Unique);

	ovl.GetLog().Info("Texture::CopyDataTo(..): Created texture \"" + _name + "\"");
}

StructureHeader Texture::GetHeader()
{
	StructureHeader h;
	h.LoaderType = OvlLoaderType::FDGK;
	h.StructID = "tex";
	h.StructName = "Texture";
	h.TypeNumber = 2;
	return h;
}

void TextureCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(Texture::GetHeader());

	unsigned int size = sizeof(TextureRawData) * _structs.size();

	ovl.GetLog().Debug("TEX entry size = " + STR(size));

	DataEntry& entry = ovl.CreateEntry(OvlType::Unique, 2, size);

	TextureRawData* raw = (TextureRawData*)entry.Data;

	for (int i = 0; i < _structs.size(); i++)
	{
		_structs[i]->CopyDataTo(ovl, &raw[i], headerIndex);
	}
}