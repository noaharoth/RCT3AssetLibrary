// Queue.cpp

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

#include "stdafx.hpp"
#include "Queue.hpp"

using namespace RCT3Asset;

Queue::Queue() 
{ 
}

void Queue::Name(std::string name)
{
	_name = name;
}

std::string Queue::Name() const
{
	return _name;
}

std::string Queue::GetNameID() const
{
	return _name + ":qtd";
}

unsigned int Queue::DataSize(unsigned int file)
{
	return sizeof(QueueRawData);
}

void Queue::CopyDataTo(OvlFile& ovl, QueueRawData* queue, unsigned int headerIndex)
{
	ovl.AddString(GetNameID(), nullptr);

	queue->ResearchCategories = nullptr; //todo
	queue->ResearchCategoryCount = 0;  // todo

	ovl.AddString(_name, &queue->Name);
	ovl.AddPointer(Ptr(queue->Name));

	ovl.AddString(Straight, &queue->Straight);
	ovl.AddPointer(Ptr(queue->Straight));
	ovl.AddString(TurnL, &queue->TurnL);
	ovl.AddPointer(Ptr(queue->TurnL));
	ovl.AddString(TurnR, &queue->TurnR);
	ovl.AddPointer(Ptr(queue->TurnR));
	ovl.AddString(SlopeUp, &queue->SlopeUp);
	ovl.AddPointer(Ptr(queue->SlopeUp));
	ovl.AddString(SlopeDown, &queue->SlopeDown);
	ovl.AddPointer(Ptr(queue->SlopeDown));
	ovl.AddString(SlopeStraight1, &queue->SlopeStraight1);
	ovl.AddPointer(Ptr(queue->SlopeStraight1));
	ovl.AddString(SlopeStraight2, &queue->SlopeStraight2);
	ovl.AddPointer(Ptr(queue->SlopeStraight2));

	Identifier id(GetNameID());
	id.AssignData(queue);

	DataInfo info(headerIndex, queue, id, 3);

	Reference txtRef(&queue->Text, Text.NameID());
	ovl.AddString(Text.NameID(), nullptr);
	Reference gsiRef(&queue->Icon, GsiIcon.NameID());
	ovl.AddString(GsiIcon.NameID(), nullptr);
	Reference ftxRef(&queue->Texture, FtxTexture.NameID());
	ovl.AddString(FtxTexture.NameID(), nullptr);
	txtRef.AssignOwner(info);
	gsiRef.AssignOwner(info);
	ftxRef.AssignOwner(info);

	ovl.AddIdentifier(id, OvlType::Unique);
	ovl.AddDataInfo(info, OvlType::Unique);
	ovl.AddReference(txtRef, OvlType::Unique);
	ovl.AddReference(gsiRef, OvlType::Unique);
	ovl.AddReference(ftxRef, OvlType::Unique);

	ovl.GetLog().Info("Queue::CopyDataTo(..): Created queue \"" + _name + "\"");
}

StructureHeader Queue::GetHeader()
{
	StructureHeader h;
	h.StructName = "QueueType";
	h.StructID = "qtd";
	h.LoaderType = OvlLoaderType::RCT3;
	h.TypeNumber = 1;
	return h;
}

void QueueCollection::AddTo(OvlFile& ovl)
{
	unsigned int headerIndex = ovl.AddStructureHeader(Queue::GetHeader());

	unsigned int size = 0;

	for (auto p : _structs)
	{
		size += p.DataSize(OvlType::Unique);
	}

	DataEntry& entry = ovl.CreateEntry(OvlType::Unique, 2, size);

	QueueRawData* data = reinterpret_cast<QueueRawData*>(entry.Data);

	for (int i = 0; i < _structs.size(); i++)
	{
		_structs[i].CopyDataTo(ovl, &data[i], headerIndex);
	}
}