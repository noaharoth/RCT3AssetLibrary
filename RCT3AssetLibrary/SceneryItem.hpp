// SceneryItem.hpp

#pragma once

#include "stdafx.hpp"
#include "SceneryItemRaw.hpp"
#include "OvlFile.hpp"
#include "StructRef.hpp"
#include "StructureCollection.hpp"

namespace RCT3Asset
{

	class Parameter
	{
	public:
		std::string Type;
		std::string Parameters;
	};

	class PositionData
	{
	public:
		unsigned int Flags;
		unsigned int HeightMin;
		unsigned int HeightMax;
		unsigned int SupportsType;

		PositionData();

		unsigned int ActualHeight() const;

		unsigned int DataSize() const;

		void CopyDataTo(OvlFile& ovl, PositioningRawData* pos, unsigned int* data);
	};

	class SceneryItem
	{
	private:
		std::string _name;

	public:
		unsigned int Unknown01;
		unsigned int Flags;
		unsigned short PositioningType;
		unsigned short AddonPack;
		unsigned int Unknown02;
		unsigned int XSquareCount;
		unsigned int ZSquareCount;
		std::vector<PositionData> PositioningData;
		Vector3 Position;
		Vector3 Size;
		//std::vector<StructRef<Track>> Tracks;
		unsigned int Cost;
		unsigned int Refund;
		unsigned int Unknown03;
		unsigned int SceneryItemType;
		std::string Supports;
		std::vector< StructRef< SceneryItemVisual > > Svds;
		StructRef<GuiSkinItem> GsiIcon;
		StructRef<GuiSkinItem> GsiGroupIcon;
		StructRef<TextString> TxtGroupName;
		std::string OvlPath;
		std::vector<Parameter> Parameters;
		//std::vector<StructRef<Sound>> Sounds;
		StructRef<TextString> TxtName;
		unsigned int Unknown04;
		unsigned int Unknown05;
		unsigned int StallUnknown01;
		unsigned int StallUnknown02;
		GameColor DefaultColors;
		unsigned int Unknown06;
		unsigned int Unknown07;
		unsigned int Unknown08;
		unsigned int Unknown09;
		unsigned int Unknown10;
		unsigned int Unknown11;
		unsigned int Unknown12;
		unsigned int Unknown13;
		//unsigned int AnrNameCount;
		//void* AnrNames;
		unsigned int Unknown14;
		//unsigned int AnrAgeAlternatives;
		//unsigned int AnrChunks;
		//unsigned int AnrAlternateRunAnimations;
		//unsigned int AnrCyclesPerCircuit;

		SceneryItem();

		void Name(std::string name);

		std::string Name() const;

		std::string GetNameID() const;

		unsigned int GetDataSize(unsigned int file);

		void CopyDataTo(OvlFile& ovl, unsigned char* unique, unsigned char* common, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};


	class SceneryItemCollection final : public StructureCollection < SceneryItem >
	{
	public:

		void AddTo(OvlFile& ovl);

	};

}