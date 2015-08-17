// ManifoldMeshRaw.hpp

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

#pragma once

#include "stdafx.hpp"
#include "Vertex.hpp"

namespace RCT3Asset
{

	// Manifold mesh vertex
	struct MMVertex
	{
		Vector3 Position;
		unsigned int Unknown;

		MMVertex() : Position(), Unknown(0) { }
	};

	struct ManifoldMeshRawData
	{
		MMVertex BoundingBoxMin;
		MMVertex BoundingBoxMax;
		unsigned int VertexCount;
		unsigned int FaceCount;
		MMVertex* Vertices;
		unsigned short* Indices;
	};

}