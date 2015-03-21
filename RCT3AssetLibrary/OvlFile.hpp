// OvlFile.h

#pragma once

#include "stdafx.hpp"
#include "FileSections.hpp"
#include "OvlRaw.hpp"
#include "OvlIdentifierTable.hpp"
#include "OvlDataInfoTable.hpp"
#include "OvlReferenceTable.hpp"
#include "OvlPointerTable.hpp"
#include "OvlStringTable.hpp"
#include "OutputLog.hpp"

namespace RCT3Asset
{

	void InitializeRCT3AssetLibrary(const char* _arg);

	class OvlFile
	{
	private:

		// Disable copying
		OvlFile(const OvlFile&) = delete;
		OvlFile& operator=(const OvlFile&) = delete;

		RCT3Debugging::OutputLog& _log;

		void _fixStrings();

		void _createIdentifierTables();

		void _createDataInfoTables();

		void _createReferenceTables();

		void _createPointerTables();

		void CreateTables();

		OvlHeader Header;
		FileSections Sections[2];
		OvlStringTable StringTable;
		OvlPointerTable PointerTable;
		OvlIdentifierTable IdentifierTable;
		OvlDataInfoTable DataInfoTable;
		OvlReferenceTable ReferenceTable;
		std::queue<std::pair<std::string, OvlString*>> FollowStrings; // updates string pointers
		std::vector<StructureHeader> StructureHeaders;
		std::vector<std::string> FileReferences;
		std::vector<ExtraData> OvlExtraData[2];

	public:
		OvlFile(RCT3Debugging::OutputLog& log) : _log(log) { }

		// * Adds a string to the StringTable.
		// @param location: The location of the string pointer in raw data.
		void AddString(std::string str, OvlString* location);

		// Adds a pointer to the PointerTable.
		void AddPointer(unsigned int* pointer);

		// Adds a file reference to the OvlFile.
		void AddFileReference(std::string reference);

		// Adds an Identifier to the IdentifierTable.
		void AddIdentifier(Identifier id, unsigned int file);

		// Adds a DataInfo to the DataInfoTable.
		void AddDataInfo(DataInfo info, unsigned int file);

		// Adds a Reference to the ReferenceTable.
		void AddReference(Reference reference, unsigned int file);

		// Creates and adds ExtraData to the specified OVL file.
		ExtraData CreateAndAddExtraData(unsigned int size, unsigned int file);

		// Adds a StructureHeader to the OvlFile, and returns the index of that StructureHeader.
		unsigned int AddStructureHeader(StructureHeader header);

		// Returns the index of the specified StructureHeader. Used by DataInfos.
		unsigned int GetStructureHeaderIndex(StructureHeader header);

		// Creates and returns a new DataEntry in the specified location.
		DataEntry& CreateEntry(unsigned int file, unsigned int section, unsigned int size);

		// * Returns the OutputLog contained in this OvlFile.
		RCT3Debugging::OutputLog& GetLog() const;

		// * Saves the OVL file data to the specified file name.
		// @param filename: File name WITHOUT extension!
		void Save(std::string filename);

		~OvlFile();
	};

}