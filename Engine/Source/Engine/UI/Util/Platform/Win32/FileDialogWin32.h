#pragma once

#include <Engine/Challenge.h>
#include <Engine/UI/Util/FileDialog.h>

namespace challenge
{
	template<>
	class _FileDialog<PlatformTypeWin32>
	{
	public:
		static std::vector<std::wstring> OpenFileDialog(OPEN_FILE_DIALOG_DESC desc = OPEN_FILE_DIALOG_DESC());
		static bool SaveFileDialog(SAVE_FILE_DIALOG_DESC desc = SAVE_FILE_DIALOG_DESC());
	};
}