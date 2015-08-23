// OvlImage.hpp
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

#pragma once

#include <string>
#include <IL/il2.h>
#include <IL/ilu2.h>

namespace RCT3Asset
{

	// A wrapper class that incorporates functionality from ResIL
	// that pertains to OVL image format.
	class OvlImage
	{
	private:
		ILimage* _image;

	protected:

		static bool _resILInitialized;

		static bool _resILInit()
		{
			il2Init();

			ILenum error = il2GetError();

			if (error != IL_NO_ERROR)
			{

			}

			ilu2Init();
		}

	};

}