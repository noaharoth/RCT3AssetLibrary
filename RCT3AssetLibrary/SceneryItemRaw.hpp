// SceneryItemRaw.hpp

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
#include "Vertex.hpp"
#include "GuiSkinItem.hpp"
#include "TextString.hpp"

namespace RCT3Asset
{
	struct SceneryItemVisualRawData
	{
		// PLACEHOLDER FOR SAKE OF READABILITY (WILL BE RELOCATED)
	};

	class SceneryItemVisual
	{
		// PLACEHOLDER FOR SAKE OF READABILITY (WILL BE RELOCATED)
	};

	typedef SceneryItemVisualRawData* SvdPtr;

	struct ParameterRawData
	{
		OvlString Type;
		OvlString Parameters;
	};

	struct PositioningRawData
	{
		unsigned int Flags;
		unsigned int HeightMin;
		unsigned int HeightMax;
		unsigned int* Data;
		unsigned int SupportsType;
	};

	struct SceneryItemRawData
	{
		unsigned int Unknown01;
		unsigned int Flags;
		unsigned short PositioningType;
		unsigned short AddonPack;
		unsigned int Unknown02;
		unsigned int XSquareCount;
		unsigned int ZSquareCount;
		PositioningRawData* PositionData;
		Vector3 Position;
		Vector3 Size;
		unsigned int TrackCount;
		void* Tracks;
		unsigned int Cost;
		unsigned int Refund;
		unsigned int Unknown03;
		unsigned int SceneryItemType;
		OvlString Supports;
		unsigned int SvdCount;
		SvdPtr* Svds;
		GsiPtr GsiIcon;
		GsiPtr GsiGroupIcon;
		TxtPtr TxtGroupName;
		OvlString OvlPath;
		unsigned int ParameterCount;
		ParameterRawData* Parameters;
		unsigned int SoundCount;
		void* Sounds;
		TxtPtr TxtName;
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
		unsigned int AnrNameCount;
		void* AnrNames;
		unsigned int Unknown14;
		unsigned int AnrAgeAlternatives;
		unsigned int AnrChunks;
		unsigned int AnrAlternateRunAnimations;
		unsigned int AnrCyclesPerCircuit;
	};

	// -------- Below are values discovered by Jonwil/Belgabor, and borrowed from their include files. Many thanks for their AWESOME work!! ------- //

	struct SIDPositionType 
	{
		enum 
		{
			Full,
			PathEdgeInner,
			PathEdgeOuter,
			Wall,
			Quarter,
			Half,
			Center,
			Corner,
			PathEdgeJoin
		};
	};

	struct SquareFlags 
	{
		enum 
		{
			Collision = 1,
			Supports
		};
	};

	struct SIDType 
	{
		enum 
		{
			Tree,
			Plant,
			Shrub,
			Flowers,
			Fence,
			WallMisc,
			PathLamp,
			ScenerySmall,
			SceneryMedium,
			SceneryLarge,
			SceneryAnamatronic,
			SceneryMisc,
			SupportMiddle,
			SupportTop,
			SupportBottom,
			SupportBottomExtra,
			SupportGirder,
			SupportCap,
			RideTrack,
			Path,
			ParkEntrance,
			Litter,
			GuestInject,
			Ride,
			RideEntrance,
			RideExit,
			KeepClearFence,
			Stall,
			RideEvent,
			Firework,
			LitterBin,
			Bench,
			Sign,
			PhotoPoint,
			WallStraight,
			WallRoof,
			WallCorner,
			WaterCannon,
			PoolPiece,
			PoolExtra,
			ChangingRoom,
			LaserDome,
			WaterJet,
			TerrainPiece,
			ParticleEffect,
			AnimalFence,
			AnimalMisc,
		};
	};

}