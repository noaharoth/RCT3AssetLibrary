// Queue.h

#pragma once

#include "stdafx.hpp"
#include "OvlFile.hpp"
#include "QueueRaw.hpp"
#include "TextString.hpp"
#include "GuiSkinItem.hpp"
#include "FlexiTexture.hpp"
#include "StructRef.hpp"
#include "StructureCollection.hpp"

namespace RCT3Asset
{
	
	class Queue
	{
	private:
		std::string _name;

	public:
		StructRef<TextString> Text;
		StructRef<GuiSkinItem> GsiIcon;
		StructRef<FlexiTexture> FtxTexture;
		std::string Straight;
		std::string TurnL;
		std::string TurnR;
		std::string SlopeUp;
		std::string SlopeDown;
		std::string SlopeStraight1;
		std::string SlopeStraight2;

		Queue();

		void Name(std::string name);

		std::string Name() const;

		std::string GetNameID() const;

		unsigned int DataSize(unsigned int file);

		void CopyDataTo(OvlFile& ovl, QueueRawData* queue, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};


	class QueueCollection final : public StructureCollection < Queue >
	{
	public:

		void AddTo(OvlFile& ovl);

	};

}