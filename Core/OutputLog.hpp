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
	typedef void(*ErrorCallback)(OutputLog& log, std::string& message);

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

		__forceinline std::string _currentDateTime();

	public:

		OutputLog();

		OutputLog(ErrorCallback callback);

		// * Assigns a std::ostream derived class to the OutputLog.
		void AssignStream(std::ostream* outStream);

		void EnableDebugging();

		void Debug(std::string message);

		void Info(std::string message);

		void Warning(std::string message);

		void Error(std::string message);

		void SaveToFile(std::string filename);

		unsigned int ErrorCount() const;

		std::string GetErrors() const;

	};

}