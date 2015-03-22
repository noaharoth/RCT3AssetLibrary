// OvlImage.cpp

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
#include "OvlImage.hpp"

using namespace RCT3Asset;

OvlImage::OvlImage(RCT3Debugging::OutputLog& log)
	: _isValid(false), _log(log)
{

}

OvlImage::OvlImage(const std::string& imageFile, RCT3Debugging::OutputLog& log)
	: _log(log), _isValid(false)
{
	FromFile(imageFile);
}

bool OvlImage::FromFile(const std::string& imageFile)
{
	try
	{
		_image.read(imageFile);

		std::string possibleErrors = "";

		if (!Check(possibleErrors))
		{
			_log.Error("OvlImage::FromFile(...): Image unfit for RCT3: " +
				possibleErrors +
				"\tImage file: " + imageFile);

			return _isValid = false;
		}

		return true;
	}
	catch (Magick::Exception& e)
	{
		_log.Error("OvlImage::FromFile(...): Error reading image: " +
			std::string(e.what()) +
			"\n\tImage file: " + imageFile);
		return _isValid = false;
	}
}

bool OvlImage::Check(std::string& out_msg)
{
	bool ok = true;

	if (Width() != Height())
	{
		ok = false;
		out_msg += "\tImage must be square!\n";
	}

	if (!_isPowerOf2(Dimension()))
	{
		ok = false;
		out_msg += "\tImage must be a power of two!\n";
	}

	if (Dimension() > 2048)
	{
		ok = false;
		out_msg += "\tImage size must not exceed 2048x2048!\n";
	}

	return ok;
}

inline bool OvlImage::HasAlpha() const
{
	if (_isValid)
		return _image.matte();

	_log.Error("OvlImage::HasAlpha(...): Tried to access invalid image");

	return false;
}

inline unsigned int OvlImage::Width() const
{
	if (_isValid)
		return _image.rows();

	_log.Error("OvlImage::Width(...): Tried to access invalid image");

	return 0;
}

inline unsigned int OvlImage::Height() const
{
	if (_isValid)
		return _image.columns();

	_log.Error("OvlImage::Height(...): Tried to access invalid image");

	return 0;
}

inline unsigned int OvlImage::Dimension() const
{
	if (_isValid)
		return _image.columns();

	_log.Error("OvlImage::Dimension(...): Tried to access invalid image");

	return 0;
}

bool OvlImage::_isPowerOf2(unsigned int x)
{
	return ((x > 0) && ((x & (x - 1)) == 0));
}