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

	struct SIDPositionType 
	{
		enum 
		{
			Tile_Full = 0,
			Path_Edge_Inner = 1,
			Path_Edge_Outer = 2,
			Wall = 3,
			Tile_Quarter = 4,
			Tile_Half = 5,
			Path_Center = 6,
			Corner = 7,
			Path_Edge_Join = 8
		};
	};

	struct SIDFlags 
	{
		enum 
		{
			Unknown_01 = 0x00000001,
			Unknown_02 = 0x00000002, ///< Never set?
			Unknown_03 = 0x00000004,
			Unknown_04 = 0x00000008,
			Delete_On_Ground_Change = 0x00000010,
			Ground_Change = 0x00000020, ///< Goes with ground if non-colliding, blocks ground change otherwise
			Unknown_07 = 0x00000040,
			Unknown_08 = 0x00000080,
			Support_Block = 0x00000100, ///< Blocks supports (from above only, may require collision detection)?
			///< Set on terrain blocks and courtyard column
			Unknown_10 = 0x00000200, ///< Several of Track2-Track6, Track8-Track15, Track18, Track22, Track24, Track26-Track36, Track59, Track60
			///<   TrackBased01-TrackBased04, TrackBased07, TrackBased14, TrackBased21-TrackBased24, TrackBased33, TrackBased37
			///< TrackBased10, TrackBased12: SteepSlopeDown
			Unknown_11 = 0x00000400, ///< Few of Track20;
			///< Most of Track3, Track31, Track33_CT, Track34 (those that do not have Flag27), Track35, Track59, TrackBased09, TrackBased22
			///< All sections of Track2, Track4 - Track6, Track8 - Track15, Track18, Track22, Track24, Track26-Track29, Track32, Track36, Track60,
			///<   TrackBased01-TrackBased04, TrackBased07-TrackBased08, TrackBased14, TrackBased21, TrackBased23, TrackBased24, TrackBased33, TrackBased37
			Unknown_12 = 0x00000800, ///< Some sections of Track6, Track9, Track10, Track60; Most sections of Track8, Track12, Track13, TrackBased04
			Skew = 0x00001000, ///< Object skews with ground (like fences). Might depend on other things
			Smooth_Height = 0x00002000, ///< Smooth height change, not in increments.
			Unknown_15 = 0x00004000, ///< Some Supports: ts2, ts3
			Unknown_16 = 0x00008000, ///< Some Supports: ts5
			On_Water_Only = 0x00010000, ///< Removes base of flats and makes them placable on water only. Asso on some stations
			Unknown_18 = 0x00020000, ///< Never set
			Unknown_19 = 0x00040000, ///< Never set
			Ride_Leave_After_Stop = 0x00080000, ///< Peeps leave from end of stop animation instead of idle.
			Unknown_21 = 0x00100000, ///< Track33_CT, Vertical chain; Trackbased21, Bowl and Funnel
			Ride_Exact_Fence = 0x00200000, ///< On rides, fence only around parts touching the floor (collision detection)
			Unknown_23 = 0x00400000, ///< All ride events
			Fences = 0x00800000, ///< Set for fences and fence-like objects. Purpose unknown.
			Unknown_25 = 0x01000000, ///< Jungle Trees
			Billboard_Menu = 0x02000000, ///< Puts object in billboard menu
			Unknown_27 = 0x04000000, ///< Right part of joint sections for the splitting cosater
			Unknown_28 = 0x08000000, ///< Never set
			Unknown_29 = 0x10000000, ///< Never set?
			Unknown_30 = 0x20000000, ///< Never set?
			Unknown_31 = 0x40000000, ///< Never set?
			Unknown_32 = 0x80000000, ///< Never set?
		};
	};

	struct SquareFlags 
	{
		enum 
		{
			Collision = 0x00000001, ///< Activates collision detection
			Supports = 0x00000002, ///< Show supports. Needs Collision and the respective setting
			Unknown_35 = 0x00000004, ///< Never set?
			Unknown_36 = 0x00000008,
			Unknown_37 = 0x00000010,
			Unknown_38 = 0x00000020,
			Unknown_39 = 0x00000040,
			Unknown_40 = 0x00000080,
			Unknown_41 = 0x00000100,
			Unknown_42 = 0x00000200,
			Unknown_43 = 0x00000400,
			Unknown_44 = 0x00000800
		};
	};

	struct SIDType 
	{
		enum 
		{
			Tree = 0,
			Plant = 1,
			Shrub = 2,
			Flowers = 3,
			Fence = 4,
			Wall_Misc = 5,
			Path_Lamp = 6,
			Scenery_Small = 7,
			Scenery_Medium = 8,
			Scenery_Large = 9,
			Scenery_Anamatronic = 10,
			Scenery_Misc = 11,
			Support_Middle = 12,
			Support_Top = 13,
			Support_Bottom = 14,
			Support_Bottom_Extra = 15,
			Support_Girder = 16,
			Support_Cap = 17,
			Ride_Track = 18,
			Path = 19,
			Park_Entrance = 20,
			Litter = 21,
			Guest_Inject = 22,
			Ride = 23,
			Ride_Entrance = 24,
			Ride_Exit = 25,
			Keep_Clear_Fence = 26,
			Stall = 27,
			Ride_Event = 28,
			Firework = 29,
			Litter_Bin = 30,
			Bench = 31,
			Sign = 32,
			Photo_Point = 33,
			Wall_Straight = 34,
			Wall_Roof = 35,
			Wall_Corner = 36,
			//new for Soaked!
			Water_Cannon = 37,
			Pool_Piece = 38,
			Pool_Extra = 39,
			Changing_Room = 40,
			Laser_Dome = 41, //???
			Water_Jet = 42, //???
			Terrain_Piece = 43, //???
			Particle_Effect = 44, //???
			//new for Wild!
			Animal_Fence = 45, //???
			Animal_Misc = 46  //???
		};
	};

}