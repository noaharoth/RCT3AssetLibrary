// StaticShapeRaw.hpp

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
*/

#include "stdafx.hpp"
#include "Vertex.hpp"
#include "FlexiTextureRaw.hpp"
#include "TextureStyle.hpp"

namespace RCT3Asset
{
	struct BoundingBox
	{
		Vector3 Min;
		Vector3 Max;
	};

	struct StaticMeshRawData
	{
		unsigned int SupportType;
		FtxRef FtxTexture;
		TxsRef TextureStyle;
		unsigned int TexturePreview;
		unsigned int Flags;
		unsigned int Sidedness;
		unsigned int VertexCount;
		unsigned int IndexCount;
		Vertex* Vertices;
		unsigned int* Indices;
	};

	struct StaticShapeRawData
	{
		BoundingBox BBox;
		unsigned int VertexCount;
		unsigned int IndexCount;
		unsigned int Unknown; // is meshcount2 in libOVL, but is always set to 0?
		unsigned int MeshCount;
		StaticMeshRawData* Meshes;
		unsigned int EffectCount;
		Matrix4x4* EffectPositions;
		OvlString* EffectNames;
	};

	typedef StaticShapeRawData* ShsRef;
}