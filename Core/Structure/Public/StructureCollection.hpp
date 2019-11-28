// StructureCollection.hpp

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
#include "OvlFile.hpp"

namespace RCT3Asset
{

	template < class TStructure >
	// * Base class for a StructureCollection.
	// * StructureCollections should be used even if there is only one
	//   structure to be added to the OvlFile. This saves you the hassle
	//   of having to allocate data entries manually.
	class StructureCollection
	{
	protected:
		std::vector<TStructure> _structs;

	public:

		//virtual void AddTo(OvlFile& ovl) = 0; <---- no need for this to be virtual

		void Add(TStructure& structure)
		{
			_structs.push_back(structure);
		}

		unsigned int Count() const
		{
			return _structs.size();
		}
	};

}