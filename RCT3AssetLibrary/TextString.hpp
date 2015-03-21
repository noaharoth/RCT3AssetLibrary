// Text.h

#pragma once

#include "stdafx.hpp"
#include "OvlFile.hpp"
#include "StructureCollection.hpp"

namespace RCT3Asset
{
	typedef wchar_t TextStringRawData;
	typedef wchar_t* TxtPtr;

	class TextString
	{
	private:
		std::wstring _text;
		std::string _name;
	public:

		TextString();

		TextString(std::string name, std::wstring text);

		unsigned int DataSize(unsigned int file);

		unsigned int Length() const;

		std::string GetNameID() const;

		std::string Name() const;

		void Name(std::string name);

		std::wstring Text() const;

		void Text(std::wstring text);

		void CopyDataTo(OvlFile& ovl, TextStringRawData* data, unsigned int headerIndex);

		static StructureHeader GetHeader();
	};

	class TextStringCollection final : public StructureCollection < TextString >
	{
	public:

		void AddTo(OvlFile& ovl);

	};
}