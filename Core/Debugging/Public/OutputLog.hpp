// OutputLog.hpp

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
#include <Windows.h>

namespace RCT3Debugging
{

	class OutputLog;

	// Gets invoked after first error is reached.
	// @param userData: Used by C++/CLI for interop with .NET managed code.
	typedef void(*ErrorCallback)(OutputLog& sender, std::string& message, void* userData);

	// OutputLog interface.
	class OutputLog
	{
	private:
		std::ostream* _out;
		std::stringstream _stringStream;
		bool _debugging;

		unsigned int _currentLine;
		unsigned int _errorCount;
		std::stringstream _errorStream;

		ErrorCallback _callback;
		void* _userData;

		__forceinline std::string _currentDateTime();

	public:

		OutputLog();

		// Assigns a std::ostream derived class to the OutputLog.
		void AssignStream(std::ostream* outStream);

		// Assigns an ErrorCallback to the OutputLog.
		// @param userData: to be used for interop with managed code.
		void AssignCallback(ErrorCallback callback, void* userData = nullptr);

		// Enables debugging messages to be logged.
		void EnableDebugging();

		// Adds a debug message to the OutputLog.
		void Debug(std::string message);

		// Adds an information message to the OutputLog.
		void Info(std::string message);

		// Adds a warning message to the OutputLog.
		void Warning(std::string message);

		// Adds an error message to the OutputLog.
		// If an ErrorCallback was supplied via AssignCallback,
		// it will be invoked upon recieving an error message.
		void Error(std::string message);

		// Saves the log to the specified file.
		void SaveToFile(std::string filename);

		// Returns the amount of errors.
		unsigned int ErrorCount() const;
	
		// Returns a list of errors.
		std::string GetErrors() const;

	};

}