// OvlImage.hpp
// No longer using GraphicsMagick and libsquish, instead using ResIL

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

#pragma once

#include "stdafx.hpp"

namespace RCT3Asset
{

	struct BGRAColor
	{
		unsigned char B;
		unsigned char G;
		unsigned char R;
		unsigned char A;

		BGRAColor() : B(0), G(0), R(0), A(0) { }

		BGRAColor(unsigned char b, unsigned char g, unsigned char r, unsigned char a) : B(b), G(g), R(r), A(a) { }
	};

	struct RGBAColor
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
		unsigned char A;

		RGBAColor() : R(0), G(0), B(0), A(0) { }

		RGBAColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : R(r), G(g), B(b), A(a) { }
	};

	struct RGBColor
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;

		RGBColor() : R(0), G(0), B(0) { }

		RGBColor(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b) { }
	};

	// A wrapper class that incorporates functionality from ResIL \
	 that pertains to the OVL image format.
	class OvlImage
	{
	protected:
		ILimage* _image;
		RCT3Debugging::OutputLog& _log;
		unsigned int _width;
		unsigned int _height;
		bool _hasAlpha;

		static bool _resILInitialized;

		bool _resILInit();

	public:

		// Disable copying!
		OvlImage(const OvlImage&) = delete;
		OvlImage& operator=(const OvlImage&) = delete;

		OvlImage(RCT3Debugging::OutputLog& log);

		OvlImage(RCT3Debugging::OutputLog& log, const std::string& fileName);

		bool FromFile(const std::string& fileName);

		unsigned int Width() const;

		unsigned int Height() const;

		unsigned int Dimension() const;

		bool HasAlpha() const;

		void DeleteImage();

		virtual ~OvlImage();

	};

}