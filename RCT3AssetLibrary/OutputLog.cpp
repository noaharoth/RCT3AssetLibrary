// OutputLog.cpp

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

OutputLog::OutputLog() : _out(nullptr), _currentLine(0), _debugging(false), _errorCount(0)
{
}

void OutputLog::AssignStream(std::ostream* outStream)
{
	_out = outStream;
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