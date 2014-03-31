#pragma once

#include <Challenge/Core/Cursor.h>

namespace challenge
{
	template <>
	class __CursorPlatform<PlatformTypeWin32>
	{
		friend class Cursor;

		static void HidePlatformCursor();
		static void ShowPlatformCursor(const std::string &cursor);

		static bool sCursorVisible;
	};
};