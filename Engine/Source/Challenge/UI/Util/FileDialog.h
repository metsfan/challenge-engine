#pragma once

#include <Challenge/Challenge.h>

namespace challenge
{

	struct DialogFilter
	{
		std::wstring label;
		std::wstring extension;

		DialogFilter() {}
		DialogFilter(const std::wstring &_label, const std::wstring &_extension) :
			label(_label), extension(L"*." + _extension)
		{}
	};

	struct OPEN_FILE_DIALOG_DESC
	{
		std::wstring DefaultDirectory;
		std::vector<DialogFilter> Filters;
	};

	struct SAVE_FILE_DIALOG_DESC
	{
		std::wstring DefaultDirectory;
		std::vector<DialogFilter> Filters;
	};

	template <typename Platform>
	class _FileDialog
	{
	public:
		static std::vector<std::wstring> OpenFileDialog(OPEN_FILE_DIALOG_DESC desc = OPEN_FILE_DIALOG_DESC());
		static std::wstring SaveFileDialog(SAVE_FILE_DIALOG_DESC desc = SAVE_FILE_DIALOG_DESC());
	};

	typedef _FileDialog<CurrentPlatform> FileDialog;
}