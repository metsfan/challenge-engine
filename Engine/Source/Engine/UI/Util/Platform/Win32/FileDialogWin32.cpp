#include <Engine/Challenge.h>
#include <Engine/UI/Util/Platform/Win32/FileDialogWin32.h>
#include <Engine/Util/StringUtil.h>

namespace challenge
{
	std::vector<std::wstring> _FileDialog<PlatformTypeWin32>::OpenFileDialog(OPEN_FILE_DIALOG_DESC desc)
	{
		IFileOpenDialog *openDialog;

		std::vector<std::wstring> outFiles;

		HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<LPVOID *>(&openDialog));
		if (SUCCEEDED(hr)) {
			if (desc.Filters.size()) {
				std::vector<COMDLG_FILTERSPEC> filters;

				for (DialogFilter &filter : desc.Filters) {
					COMDLG_FILTERSPEC spec;
					spec.pszName = filter.label.c_str();
					spec.pszSpec = filter.extension.c_str();

					filters.push_back(spec);
				}

				openDialog->SetFileTypes(filters.size(), &filters[0]);
			}

			if (desc.DefaultDirectory.length()) {
				IShellItem *shellItem;
			
				std::wstring windowsPath = StringUtil::ReplaceAll<std::wstring>(desc.DefaultDirectory, L"/", L"\\");
				SHCreateItemFromParsingName(windowsPath.c_str(), NULL, IID_PPV_ARGS(&shellItem));
				openDialog->SetFolder(shellItem);
			}

			hr = openDialog->Show(NULL);
			if (SUCCEEDED(hr)) {
				IShellItemArray *items;
				hr = openDialog->GetResults(&items);
				
				DWORD count;
				items->GetCount(&count);

				PWSTR buf;

				for (int i = 0; i < count; i++) {
					IShellItem *item;
					items->GetItemAt(i, &item);

					item->GetDisplayName(SIGDN_FILESYSPATH, &buf);
					outFiles.push_back(StringUtil::ReplaceAll<std::wstring>(buf, L"\\", L"/"));
				}
			}

			openDialog->Release();
		}

		return outFiles;
	}

	bool _FileDialog<PlatformTypeWin32>::SaveFileDialog(SAVE_FILE_DIALOG_DESC desc)
	{
		return false;
	}
};