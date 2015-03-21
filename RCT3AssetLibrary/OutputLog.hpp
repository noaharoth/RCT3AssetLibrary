// OutputLog.h

#pragma once

#include "stdafx.hpp"
#include <Windows.h>

namespace RCT3Debugging
{

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

		__forceinline std::string _currentDateTime();

	public:

		OutputLog();

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