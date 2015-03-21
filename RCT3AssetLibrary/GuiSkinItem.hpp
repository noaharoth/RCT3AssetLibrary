// GuiSkinItem.h

#pragma once

#include "stdafx.hpp"
#include "GuiSkinItemRaw.hpp"
#include "Texture.hpp"
#include "StructureCollection.hpp"
#include "StructRef.hpp"
#include "OvlFile.hpp"

namespace RCT3Asset
{

	class GuiSkinItem
	{
	private:
		std::string _name;
	public:
		IconPosition Position;
		StructRef<Texture> Texture;
		unsigned int GsiType;
		unsigned int Unknown;

		GuiSkinItem();

		void Name(std::string name);

		std::string Name() const;

		std::string GetNameID() const;

		unsigned int GetDataSize(unsigned int file);

		void CopyDataTo(OvlFile& ovl, GuiSkinItemRawData* gsi, IconPosition* pos, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};


	class GuiSkinItemCollection final : public StructureCollection < GuiSkinItem >
	{
	public:

		void AddTo(OvlFile& ovl);

	};

}