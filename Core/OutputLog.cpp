// OutputLog.cpp

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
#include "OutputLog.hpp"

using namespace RCT3Debugging;

__forceinline std::string OutputLog::_currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "< %Y - %m - %d %X > - ", &tstruct);

	return buf;
}

OutputLog::OutputLog() : _out(nullptr), _currentLine(0), _debugging(false), _errorCount(0), _callback(nullptr), _userData(nullptr)
{
}

void OutputLog::AssignStream(std::ostream* outStream)
{
	_out = outStream;
}

void OutputLog::AssignCallback(ErrorCallback callback, void* userData)
{
	_callback = callback;
	_userData = userData;
}

void OutputLog::Debug(std::string message)
{
	if (_debugging)
	{
		_currentLine++;
		if (_out)
			(*_out) << _currentLine << "  " << _currentDateTime() << "<DEBUG>:\t" << message << std::endl;
		_stringStream << _currentLine << "  " << _currentDateTime() << "<DEBUG>:\t" << message << std::endl;
	}
}

void OutputLog::Info(std::string message)
{
	_currentLine++;
	if (_out)
		(*_out) << _currentLine << "  " << _currentDateTime() << "<INFO>:\t" << message << std::endl;
	_stringStream << _currentLine << "  " << _currentDateTime() << "<INFO>:\t" << message << std::endl;
}

void OutputLog::Warning(std::string message)
{
	_currentLine++;
	if (_out)
		(*_out) << _currentLine << "  " << _currentDateTime() << "<WARNING>:\t" << message << std::endl;
	_stringStream << _currentLine << "  " << _currentDateTime() << "<WARNING>:\t" << message << std::endl;
}

void OutputLog::Error(std::string message)
{
	_currentLine++;
	_errorCount++;
	if (_out)
		(*_out) << _currentLine << "  " << _currentDateTime() << "<ERROR>:\t" << message << std::endl;
	_stringStream << _currentLine << "  " << _currentDateTime() << "<ERROR>:\t" << message << std::endl;
	_errorStream << "Fatal error " << _errorCount << ": " << message << std::endl;

	if ((_errorCount - 1) == 0)
	{
		// First error, check to see if a callback was supplied and invoke it

		if (_callback != nullptr)
		{
			_callback(*this, message, _userData);
		}
	}
}

void OutputLog::SaveToFile(std::string filename)
{
	std::ofstream file;
	file.open(filename.c_str());

	if (!file.is_open())
	{
		Error("OutputLog::SaveToFile(..): unable to open/create file \"" + filename + "\", aborting.");
		return;
	}

	file << _stringStream.str();
	file.close();

	Info("Saved log file to \"" + filename + "\"");
}

void OutputLog::EnableDebugging()
{
	_debugging = true;
}

unsigned int OutputLog::ErrorCount() const
{
	return _errorCount;
}

std::string OutputLog::GetErrors() const
{
	return _errorStream.str();
}