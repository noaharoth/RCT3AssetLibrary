// Export.h

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

#ifdef R3AL_EXPORTING_DLL
#define R3AL_API __declspec(dllexport)
#elif defined(R3AL_IMPORTING_DLL)
#define R3AL_API __declspec(dllimport)
#else
#define R3AL_API
#endif