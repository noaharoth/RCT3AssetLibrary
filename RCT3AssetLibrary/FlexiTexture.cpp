// FlexiTexture.cpp

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
#include "FlexiTexture.hpp"

using namespace RCT3Asset;

inline unsigned int _local_log2(unsigned int y)
{
	unsigned int result = 0;
	while (y)
	{
		result++;
		y >>= 1;
	}
	return result - 1;
}

FlexiTextureFrame::FlexiTextureFrame(FtxImage& image) 
	: _recolor(RecolorOptions::None), _image(image)
{ 
}

unsigned int FlexiTextureFrame::Recolorability() const
{
	return _recolor;
}

void FlexiTextureFrame::Recolorability(unsigned int recolor)
{
	_recolor = recolor;
}

FtxImage& FlexiTextureFrame::GetImage()
{
	return _image;
}

unsigned int FlexiTextureFrame::Scale() const
{
	return _local_log2(_image.Dimension());
}

unsigned int FlexiTextureFrame::Dimension() const
{
	return _image.Dimension();
}


// ----------------------------------------------- //

FlexiTexture::FlexiTexture() : _fps(0), _recolor(RecolorOptions::None) 
{ 
}

std::string FlexiTexture::Name() const
{
	return _name;
}

void FlexiTexture::Name(std::string name)
{
	_name = name;
}

std::string FlexiTexture::GetNameID() const
{
	return _name + ":ftx";
}

unsigned int FlexiTexture::FramesPerSecond() const
{
	return _fps;
}

void FlexiTexture::FramesPerSecond(unsigned int fps)
{
	_fps = fps;
}

void FlexiTexture::AddFrameNumber(unsigned int number)
{
	_frameNumbers.push_back(number);
}

void FlexiTexture::AddFrame(const FlexiTextureFrame& frame)
{
	_frames.push_back(frame);
}

void FlexiTexture::MakeStillImage()
{
	_fps = 0;
	_frameNumbers.push_back(0);
}

void FlexiTexture::MakeStillImage(const FlexiTextureFrame& frame)
{
	_fps = 0;
	_frameNumbers.push_back(0);
	_frames.push_back(frame);
	_recolor = frame.Recolorability();
}

unsigned int FlexiTexture::Recolorability() const
{
	return _recolor;
}

void FlexiTexture::Recolorability(unsigned int recolor)
{
	_recolor = recolor;
}

unsigned int FlexiTexture::GetDataSize(unsigned int file)
{
	unsigned int size = sizeof(FlexiTextureRawData);
	size += _frameNumbers.size() * sizeof(unsigned int);
	size += _frames.size() * sizeof(FlexiTextureFrameRawData);
	size += (sizeof(BGRAColor) * 256) * _frames.size(); // palette
	return size;
}

void FlexiTexture::CopyDataTo(OvlFile& ovl, void* raw, unsigned int headerIndex)
{
	ovl.AddString(GetNameID(), nullptr);

	unsigned char* data = (unsigned char*)raw;

	FlexiTextureRawData* ftx = reinterpret_cast<FlexiTextureRawData*>(data);

	data += sizeof(FlexiTextureRawData);

	ftx->Scale = _frames[0].Scale();
	ftx->Height = _frames[0].Dimension();
	ftx->Width = _frames[0].Dimension();
	ftx->Recolorability = (unsigned int)_recolor;
	ftx->FramesPerSecond = _fps;
	ftx->FrameNumberCount = _frameNumbers.size();
	ftx->FramesCount = _frames.size();

	if (ftx->FrameNumberCount > 0)
	{
		ftx->FrameNumbers = (unsigned int*)data;
		data += _frameNumbers.size() * sizeof(unsigned int);
		ovl.AddPointer(Ptr(ftx->FrameNumbers));

		for (int i = 0; i < _frameNumbers.size(); i++)
		{
			ftx->FrameNumbers[i] = _frameNumbers[i];
		}
	}

	FlexiTextureFrameRawData* frames = reinterpret_cast<FlexiTextureFrameRawData*>(data);

	ftx->Frames = frames;
	data += sizeof(FlexiTextureFrameRawData) * _frames.size();
	ovl.AddPointer(Ptr(ftx->Frames));

	for (int i = 0; i < _frames.size(); i++)
	{
		frames[i].Scale = _frames[i].Scale();
		frames[i].Height = _frames[i].Dimension();
		frames[i].Width = _frames[i].Dimension();
		frames[i].Recolorability = (unsigned int)_frames[i].Recolorability();

		// palette and texture
		frames[i].PaletteData = data;
		data += sizeof(BGRAColor) * 256;
		ovl.AddPointer(Ptr(frames[i].PaletteData));

		// texture has own dataentry

		DataEntry& textureEntry = ovl.CreateEntry(COMMON, 0, _frames[i].GetImage().GetIndexedDataSize());
		frames[i].TextureData = textureEntry.Data;
		ovl.AddPointer(Ptr(frames[i].TextureData));

		bool makeRecolorable = _frames[i].Recolorability() != RecolorOptions::None;

		if (_frames[i].GetImage().HasAlpha())
		{
			DataEntry& alphaEntry = ovl.CreateEntry(COMMON, 0, _frames[i].GetImage().GetAlphaDataSize());
			frames[i].AlphaData = alphaEntry.Data;
			ovl.AddPointer(Ptr(frames[i].AlphaData));

			_frames[i].GetImage().CopyDataTo(frames[i].TextureData, frames[i].PaletteData, frames[i].AlphaData, makeRecolorable);

			ovl.GetLog().Debug("FlexiTexture::CopyDataTo(..): Copied texture, palette & alpha data from image \"" + _name + "\"");
		}
		else
		{
			_frames[i].GetImage().CopyDataTo(frames[i].TextureData, frames[i].PaletteData, nullptr, makeRecolorable);
			ovl.GetLog().Debug("FlexiTexture::CopyDataTo(..): Copied texture & palette data from image \"" + _name + "\"");
		}
	}

	Identifier id(GetNameID());
	id.AssignData(ftx);

	DataInfo info(headerIndex, ftx, id, 0);

	ovl.AddIdentifier(id, COMMON);
	ovl.AddDataInfo(info, COMMON);

	ovl.GetLog().Info("FlexiTexture::CopyDataTo(..): Created FlexiTexture \"" + _name + "\"");
}

StructureHeader FlexiTexture::GetHeader()
{
	StructureHeader h;
	h.LoaderType = FDGKLOADER;
	h.StructID = "ftx";
	h.StructName = "FlexiTexture";
	h.TypeNumber = 1;
	return h;
}

void FlexiTextureCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(FlexiTexture::GetHeader());

	unsigned int entrySize = 0;

	for (auto f : _structs)
	{
		entrySize += f->GetDataSize(COMMON);
	}

	DataEntry& entry = ovl.CreateEntry(COMMON, 2, entrySize);
	unsigned char* raw = entry.Data;

	for (auto f : _structs)
	{
		f->CopyDataTo(ovl, raw, headerIndex);
		raw += f->GetDataSize(COMMON);
	}
}