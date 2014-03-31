#include <Challenge/Challenge.h>
#include <Challenge/Core/Platform/Win32/CursorWin32.h>

namespace challenge
{
	bool __CursorPlatform<PlatformTypeWin32>::sCursorVisible = true;

	void __CursorPlatform<PlatformTypeWin32>::HidePlatformCursor()
	{
		if (sCursorVisible) {
			ShowCursor(false);
			sCursorVisible = false;
		}
		
	}

	void __CursorPlatform<PlatformTypeWin32>::ShowPlatformCursor(const std::string &cursor)
	{
		if (!sCursorVisible) {
			ShowCursor(true);
			sCursorVisible = true;
		}

		if (cursor == "arrow") {
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		else if (cursor == "crosshair") {
			SetCursor(LoadCursor(NULL, IDC_CROSS));
		}
	}
}