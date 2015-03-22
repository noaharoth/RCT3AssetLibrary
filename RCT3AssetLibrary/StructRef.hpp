// StructRef.hpp

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