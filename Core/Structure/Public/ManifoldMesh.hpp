// ManifoldMesh.hpp

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
#include "ManifoldMeshRaw.hpp"
#include "StructureCollection.hpp"
#include "OvlFile.hpp"

namespace RCT3Asset
{

	class ManifoldMesh
	{
	private:
		std::string _name;

	public:
		MMVertex BoundingBoxMin;
		MMVertex BoundingBoxMax;
		
		std::vector<MMVertex> Vertices;
		std::vector<unsigned short> Indices;

		ManifoldMesh();

		ManifoldMesh(std::string name);

		std::string Name() const;

		std::string GetNameID() const;

		unsigned int GetDataSize(unsigned int file);

		void CopyDataTo(OvlFile& ovl, unsigned char* data, unsigned int headerIndex);

		static StructureHeader GetHeader();

	};

	class ManifoldMeshCollection final : public StructureCollection < ManifoldMesh >
	{
	public:

		void AddTo(OvlFile& ovl);

	};
}