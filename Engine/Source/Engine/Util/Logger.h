#pragma once

#include <Engine/Challenge.h>

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
		static void log(LogLevel level, std::string message);
		static void log(LogLevel level, const char *format, ...);

	private:
		static bool s_OpenedOnce;
	};
};

