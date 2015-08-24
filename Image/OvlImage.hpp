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

#include <Debugging\OutputLog.hpp>

namespace RCT3Asset
{

	struct OvlImageFormat
	{
		enum
		{
			RGBA,
			RGB,
			IndexedRGB,
			IndexedRGBA
		};
	};

	// A wrapper class that incorporates functionality from ResIL \
	 that pertains to the OVL image format.
	class OvlImage
	{
	private:
		ILimage* _image;
		RCT3Debugging::OutputLog& _log;
		unsigned int _width;
		unsigned int _height;
		unsigned int _format;

	protected:

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

		void DeleteImage();

		virtual ~OvlImage();

	};

}