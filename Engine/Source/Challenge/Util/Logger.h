#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{
	typedef enum {
		LogDebug,
		LogWarning,
		LogError
	} LogLevel;

	class Logger
	{
	public:
		static void Log(LogLevel level, std::string message);
		static void Log(LogLevel level, const char *format, ...);

	private:
		static bool s_OpenedOnce;
	};
};

