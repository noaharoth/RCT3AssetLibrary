// OvlRaw.h

#pragma once

#include "stdafx.hpp"

#define OVL_SIGNATURE 0x4B524746
#define OVL_VERSION 1
#define FDGKLOADER 0x4B444746
#define RCT3LOADER 0x33544352
#define COMMON 0
#define UNIQUE 1

#define STR(val) std::to_string((val))

namespace RCT3Asset
{

	typedef char* OvlString;

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

	struct ExtraData
	{
		unsigned int Size;
		unsigned char* Data;

		ExtraData(unsigned int size, void* data) : Size(size), Data((unsigned char*)data) { }

		ExtraData() : Size(0), Data(nullptr) { }
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