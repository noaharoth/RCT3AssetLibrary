// OvlImage.hpp

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
#include "OutputLog.hpp"

namespace RCT3Asset
{

	class OvlImage
	{
	protected:
		Magick::Image _image;
		bool _isValid;
		RCT3Debugging::OutputLog& _log;

	public:

		OvlImage(RCT3Debugging::OutputLog& log);

		OvlImage(const std::string& imageFile, RCT3Debugging::OutputLog& log);

		bool FromFile(const std::string& imageFile);

		bool Check(std::string& out_msg);

		bool HasAlpha() const;

		unsigned int Width() const;

		unsigned int Height() const;

		unsigned int Dimension() const;

	protected:

		static bool _isPowerOf2(unsigned int x);

	};

}