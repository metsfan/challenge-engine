#include <Challenge/Challenge.h>
#include "Logger.h"
using namespace challenge;

bool Logger::s_OpenedOnce = false;

void Logger::Log(LogLevel level, std::string message)
{
	/*std::ofstream outfile;

	if(!Logger::s_OpenedOnce) {
		Logger::s_OpenedOnce = true;
		outfile.open("console.log", std::ios::out | std::ios::trunc);
	} else {
		outfile.open("console.log", std::ios::out | std::ios::app);
	}*/

	std::stringstream outfile;

	switch(level) {
	case LogDebug:
		outfile << " [DEBUG] ";
		break;
			
	case LogWarning:
		outfile << " [WARNING] ";
		break;

	case LogError:
		outfile << " [ERROR] ";
		break;
	}

	outfile << message + "\n";

#ifdef WIN32
	OutputDebugStringA(outfile.str().c_str());
#endif

	//outfile.close();
}

void Logger::Log(LogLevel level, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	//int len = strlen(format);
	char buffer[256];
	vsprintf(buffer, format, args);

	std::stringstream ss;
	ss << buffer;

	Logger::Log(level, ss.str());
}