// StructureCollection.h

#pragma once

#include "stdafx.hpp"
#include "OvlFile.hpp"

namespace RCT3Asset
{

	template < class TStructure >
	// * Base class for a StructureCollection.
	// * StructureCollections should be used even if there is only one
	//   structure to be added to the OvlFile. The overheard of this is minimal.
	//   Only add structures to an OvlFile manually if YOU KNOW WHAT YOU'RE DOING.
	class StructureCollection
	{
	protected:
		std::vector<TStructure*> _structs;

	public:

		//virtual void AddTo(OvlFile& ovl) = 0; <---- no need for this to be virtual

		void Add(TStructure& structure)
		{
			_structs.push_back(&structure);
		}

		unsigned int Count() const
		{
			return _structs.size();
		}
	};

}