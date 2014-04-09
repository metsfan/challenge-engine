#include <Challenge/Challenge.h>
#include <Shlwapi.h>
#include "AssetLoaderWindows.h"

namespace challenge
{
	HMODULE AssetLoader<PlatformTypeWin32>::sModule = NULL;
	std::wstring AssetLoader<PlatformTypeWin32>::sBaseFilePath;

	std::wstring AssetLoader<PlatformTypeWin32>::GetPathForAsset(const std::wstring &name)
	{
		//if(!sModule) {
			sModule = GetModuleHandle(NULL);

			sBaseFilePath.resize(MAX_PATH);
			GetModuleFileNameW(sModule, &sBaseFilePath[0], MAX_PATH);

			sBaseFilePath = sBaseFilePath.substr(0, sBaseFilePath.rfind(L"\\"));
			sBaseFilePath = StringUtil::ReplaceAll<std::wstring>(sBaseFilePath, L"\\", L"/");
		//}

		return sBaseFilePath + L"/" + name;
	}

	std::vector<std::wstring> AssetLoader<PlatformTypeWin32>::GetFilesInDirectory(const std::wstring &directory, const std::wstring &filter)
	{
		std::vector<std::wstring> mFiles;

		HANDLE hd;
		WIN32_FIND_DATAW fileData;

		if (PathFileExistsW(directory.c_str())) {
			hd = FindFirstFileW((directory + L"/" + filter).c_str(), &fileData);
		}
		else {
			std::wstring fullDirPath = AssetLoader<PlatformTypeWin32>::GetPathForAsset(directory);
			hd = FindFirstFileW((fullDirPath + L"/" + filter).c_str(), &fileData);
		}
		

		
		

		if(hd == INVALID_HANDLE_VALUE) {
			return mFiles;
		}

		do {
			if (wcscmp(fileData.cFileName, L".") == 0 ||
				wcscmp(fileData.cFileName, L"..") == 0) {
				continue;
			}

			mFiles.push_back(directory + L"/" + fileData.cFileName);
		} while(FindNextFileW(hd, &fileData));

		return mFiles;
	}
};