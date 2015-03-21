// FlicManager.h

#pragma once

#include "stdafx.hpp"
#include "FlicRaw.hpp"
#include "Texture.hpp"
#include "OvlFile.hpp"

namespace RCT3Asset
{

	class FlicManager
	{
	private:
		DataEntry _entry;
		std::vector<Texture*> _textures;

	public:

		void Add(Texture& tex);

		unsigned int GetDataSize();

		void CreateAndAssign(OvlFile& ovl);

		static StructureHeader GetHeader();

	};

}