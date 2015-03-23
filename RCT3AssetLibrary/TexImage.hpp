// TexImage.hpp

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
#include "OvlImage.hpp"
#include "Vertex.hpp"

namespace RCT3Asset
{

	struct TexImageFormat
	{
		struct DDS
		{
			enum
			{
				DXT1 = squish::kDxt1,
				DXT3 = squish::kDxt3,
				DXT5 = squish::kDxt5,
			};
		};

		enum
		{
			Default = DDS::DXT5,
			ARGB8 = 0x08
		};
	};

	// TexImage's use DXT compression methods for
	// image serialization, or just plain ARGB8 format.
	class TexImage final : public OvlImage
	{
	private:
		unsigned int _format;

	public:

		TexImage(RCT3Debugging::OutputLog& log);

		TexImage(const std::string& imageFile, unsigned int format, RCT3Debugging::OutputLog& log);

		TexImage(const std::string& imageFile, RCT3Debugging::OutputLog& log);

		unsigned int GetFlicFormat() const;

		unsigned int Blocks() const;

		unsigned int Pitch() const;

		unsigned int Format() const;

		void Format(unsigned int format);

		unsigned int GetDataSize() const;

		void CopyDataTo(void* buffer);

	};

}