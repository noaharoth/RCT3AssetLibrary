// StructRef.h

#pragma once

#include "stdafx.hpp"

namespace RCT3Asset
{

	template < class TStructure >
	class StructRef
	{
	private:
		std::string _nameID;

	public:
		StructRef() { }

		StructRef(std::string nameID) : _nameID(nameID) { }

		StructRef(TStructure& ref)
		{
			_nameID = ref.GetNameID();
		}

		std::string NameID() const
		{
			return _nameID;
		}

		StructRef& operator=(const TStructure& ref)
		{
			_nameID = ref.GetNameID();
			return *this;
		}

		StructRef& operator=(const std::string& refNameID)
		{
			_nameID = refNameID;
			return *this;
		}
	};

}