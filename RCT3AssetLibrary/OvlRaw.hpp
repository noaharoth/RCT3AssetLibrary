// OvlRaw.hpp

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

#define OVL_SIGNATURE 0x4B524746
#define OVL_VERSION 1

#define STR(val) std::to_string((val))

namespace RCT3Asset
{

	typedef char* OvlString;

	struct OvlLoaderType
	{
		enum // Not making this a strongly-typed enum (enum class) because having to cast to unsigned ints will be annoying
		{
			FDGK = 0x4B444746,
			RCT3 = 0x33544352
		};
	};

	struct OvlType
	{
		enum
		{
			Common = 0,
			Unique = 1
		};
	};

	struct OvlHeader
	{
		unsigned int Signature;
		unsigned int Reserved;
		unsigned int Version;
		unsigned int ReferenceCount;
		unsigned int Unknown01;
		unsigned int StructureCount;

		OvlHeader() : Signature(OVL_SIGNATURE), Version(OVL_VERSION), Reserved(0), ReferenceCount(0), Unknown01(0), StructureCount(0) { }
	};

	struct IdentifierRawData
	{
		OvlString NameID;
		unsigned char* Data;
		unsigned int IsPointer;
	};

	struct DataInfoRawData
	{
		unsigned int StructureHeaderIndex;
		unsigned char* Data;
		unsigned int ExtraDataCount;
		IdentifierRawData* ID;
		unsigned int ReferenceCount;
	};

	struct ReferenceRawData
	{
		unsigned int* Location;
		OvlString NameID;
		DataInfoRawData* Owner;
	};

	struct StructureHeader
	{
		unsigned int LoaderType;
		std::string StructName;
		unsigned int TypeNumber;
		std::string StructID;

		bool operator==(const StructureHeader& other) const
		{
			return StructID == other.StructID;
		}
	};

}