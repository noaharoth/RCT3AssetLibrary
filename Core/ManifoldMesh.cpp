// ManifoldMesh.cpp

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
#include "ManifoldMesh.hpp"

using namespace RCT3Asset;

ManifoldMesh::ManifoldMesh()
{

}

ManifoldMesh::ManifoldMesh(std::string name)
{
	_name = name;
}

std::string ManifoldMesh::Name() const
{
	return _name;
}

std::string ManifoldMesh::GetNameID() const
{
	return _name + ":mam";
}

unsigned int ManifoldMesh::GetDataSize(unsigned int file)
{
	unsigned int size = sizeof(ManifoldMeshRawData);
	size += Vertices.size() * sizeof(MMVertex);

	unsigned int indicesSize = Indices.size();

	if (indicesSize % 8) // padded by 8 bytes
		indicesSize += (8 - (indicesSize % 8));

	size += indicesSize * sizeof(unsigned short);

	return size;
}

void ManifoldMesh::CopyDataTo(OvlFile& ovl, unsigned char* data, unsigned int headerIndex)
{
	ovl.AddString(GetNameID(), nullptr);

	ManifoldMeshRawData* mam = reinterpret_cast<ManifoldMeshRawData*>(data);

	data += sizeof(ManifoldMeshRawData);

	mam->BoundingBoxMin = BoundingBoxMin;
	mam->BoundingBoxMax = BoundingBoxMax;
	mam->FaceCount = Indices.size() / 3;
	mam->VertexCount = Vertices.size();

	mam->Vertices = reinterpret_cast<MMVertex*>(data);
	data += Vertices.size() * sizeof(MMVertex);
	ovl.AddPointer(Ptr(mam->Vertices));

	for (int i = 0; i < Vertices.size(); i++)
		mam->Vertices[i] = Vertices[i];

	mam->Indices = reinterpret_cast<unsigned short*>(data);
	ovl.AddPointer(Ptr(mam->Indices));

	for (int i = 0; i < Indices.size(); i++)
		mam->Indices[i] = Indices[i];

	Identifier id(GetNameID());
	id.AssignData(mam);

	DataInfo info(headerIndex, mam, 0);

	ovl.AddIdentifier(id, OvlType::Common);
	ovl.AddDataInfo(info, OvlType::Common);

	ovl.GetLog().Info("ManifoldMesh::CopyDataTo(..): Created ManifoldMesh \"" + _name + "\"");
}

StructureHeader ManifoldMesh::GetHeader()
{
	StructureHeader h;
	h.LoaderType = OvlLoaderType::RCT3;
	h.TypeNumber = 1;
	h.StructID = "mam";
	h.StructName = "ManifoldMesh";
	return h;
}

void ManifoldMeshCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(ManifoldMesh::GetHeader());

	unsigned int size = 0;

	for (auto m : _structs)
		size += m.GetDataSize(OvlType::Common);

	DataEntry& commonEntry = ovl.CreateEntry(OvlType::Common, 4, size);

	unsigned char* rawData = commonEntry.Data;

	for (auto m : _structs)
	{
		m.CopyDataTo(ovl, rawData, headerIndex);
		rawData += m.GetDataSize(OvlType::Common);
	}
}