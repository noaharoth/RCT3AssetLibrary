// OvlImage.cpp
// No longer using GraphicsMagick and libsquish, instead using ResIL (DevIL)

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
*/

#include "stdafx.hpp"

#include "OvlImage.hpp"

using namespace RCT3Asset;

bool OvlImage::_resILInitialized = false;

bool OvlImage::_resILInit()
{
	if (!_resILInitialized)
	{
		il2Init();

		ILenum error = il2GetError();

		if (error != IL_NO_ERROR)
		{
			_log.Error("OvlImage::_resILInit(..): Unable to initialize ResIL (error " + std::to_string((unsigned int)error));
			return false;
		}

		ilu2Init();

		error = il2GetError();

		if (error != IL_NO_ERROR)
		{
			_log.Error("OvlImage::_resILInit(..): Unable to initialize ResIL (error " + std::to_string((unsigned int)error));
			return false;
		}

		_log.Debug("OvlImage::_resILInit(..) (static): Successfully initialized ResIL.");
		return (_resILInitialized = true);
	}
}

OvlImage::OvlImage(RCT3Debugging::OutputLog& log) : _log(log), _image(nullptr), _width(0), _height(0)
{
	_resILInit();
}

OvlImage::OvlImage(RCT3Debugging::OutputLog& log, const std::string& fileName) : _log(log), _image(nullptr), _width(0), _height(0)
{
	_resILInit();
	FromFile(fileName);
}

bool OvlImage::FromFile(const std::string& fileName)
{
	// Reassigning would just cause too many issues, so just not implementing it ATM
	if (_image != nullptr)
	{
		_log.Error("OvlImage::FromFile(..): OvlImage already assigned an image, create a new OvlImage instead.");
		return false;
	}

	ILenum error;

	_image = il2GenImage();

	if (!il2LoadImage(_image, fileName.c_str()))
	{
		error = il2GetError();
		_log.Error("OvlImage::FromFile(..): Error loading image \"" + fileName + "\" (error " +
			std::to_string((unsigned int)error) + ")");
		DeleteImage();
		return false;
	}


	ILint format;
	il2GetImageInteger(_image, IL_IMAGE_FORMAT, &format);

	// Make sure image is in a supported format
	if ((format != IL_RGB) && (format != IL_RGBA) && (format != IL_PAL_RGB32) && (format != IL_PAL_RGBA32))
	{
		// If not, attempt to convert it to a basic RGBA format
		if (!il2ConvertImage(_image, IL_RGBA, IL_UNSIGNED_BYTE))
		{
			error = il2GetError();
			_log.Error("OvlImage::FromFile(..): Error converting image \"" + fileName + "\" (error " +
				std::to_string((unsigned int)error) + ")");
			DeleteImage();
			return false;
		}
		else
		{
			_format = OvlImageFormat::RGBA;
		}
	}

	switch (format)
	{
		case IL_RGB:
			_format = OvlImageFormat::RGB;
			break;
		case IL_RGBA:
			_format = OvlImageFormat::RGBA;
			break;
		case IL_PAL_RGB32:
			_format = OvlImageFormat::IndexedRGB;
			break;
		case IL_PAL_RGBA32:
			_format = OvlImageFormat::IndexedRGBA;
			break;
		default:
			// Attempt to convert it to a basic RGBA format
			if (!il2ConvertImage(_image, IL_RGBA, IL_UNSIGNED_BYTE))
			{
				error = il2GetError();
				_log.Error("OvlImage::FromFile(..): Error converting image \"" + fileName + "\" (error " +
					std::to_string((unsigned int)error) + ")");
				DeleteImage();
				return false;
			}
			else
			{
				_format = OvlImageFormat::RGBA;
				break;
			}
	}

	ILint w, h;

	il2GetImageInteger(_image, IL_IMAGE_WIDTH, &w);
	il2GetImageInteger(_image, IL_IMAGE_HEIGHT, &h);

	// Check if image is square
	if (w != h)
	{
		_log.Error("OvlImage::FromFile(..): Image must be square! (" + std::to_string((unsigned int)w) +
			std::to_string((unsigned int)h) + ")");
		DeleteImage();
		return false;
	}

	// Check if image is power of 2
	if ((h > 0) && ((h & (h - 1)) != 0))
	{
		_log.Error("OvlImage::FromFile(..): Image must be a power of 2!");
		DeleteImage();
		return false;
	}

	// Check if image is less than 2048 in size
	if (h > 2048)
	{
		_log.Error("OvlImage::FromFile(..): Image must not exceed 2048x2048!");
		DeleteImage();
		return false;
	}

	// We are good to go!
	_width = w;
	_height = h;

	_log.Info("OvlImage::FromFile(..): Successfully loaded image \"" + fileName + "\"");

	return true;
}

unsigned int OvlImage::Width() const
{
	return _width;
}

unsigned int OvlImage::Height() const
{
	return _height;
}

unsigned int OvlImage::Dimension() const
{
	return _height;
}

void OvlImage::DeleteImage()
{
	if (_image)
	{
		il2DeleteImage(_image);
		_image = nullptr;
		_width = 0;
		_height = 0;
		_log.Debug("OvlImage::DeleteImage(..): Successfully deleted image.");
	}
}

OvlImage::~OvlImage()
{
	DeleteImage();
}