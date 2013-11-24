#pragma once

#include <Engine/Challenge.h>

namespace challenge
{
	struct SAVE_FILE_DIALOG_DESC
	{
		std::wstring DefaultDirectory;
		std::wstring Extension;
	};

	struct DialogFilter
	{
		std::wstring label;
		std::wstring extension;

		DialogFilter() {}
		DialogFilter(const std::wstring &_label, const std::wstring &_extension) :
			label(_label), extension(_extension)
		{}
	};

	struct OPEN_FILE_DIALOG_DESC
	{
		std::wstring DefaultDirectory;
		std::vector<DialogFilter> Filters;
	};

	template <typename Platform>
	class _FileDialog
	{
	public:
		static std::vector<std::wstring> OpenFileDialog(OPEN_FILE_DIALOG_DESC desc = OPEN_FILE_DIALOG_DESC());
		static bool SaveFileDialog(SAVE_FILE_DIALOG_DESC desc = SAVE_FILE_DIALOG_DESC());
	};

	typedef _FileDialog<CurrentPlatform> FileDialog;
}