#pragma once

#include <Challenge/Challenge.h>
#include <Challenge/UI/Util/FileDialog.h>

namespace challenge
{
	template<>
	class _FileDialog<PlatformTypeWin32>
	{
	public:
		static std::vector<std::wstring> OpenFileDialog(OPEN_FILE_DIALOG_DESC desc = OPEN_FILE_DIALOG_DESC());
		static std::wstring SaveFileDialog(SAVE_FILE_DIALOG_DESC desc = SAVE_FILE_DIALOG_DESC());
	};
}