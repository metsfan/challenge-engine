#include <Challenge/Challenge.h>
#include <Challenge/UI/Platform/Win32/WindowWin32.h>

namespace challenge
{
	WindowWin32::WindowWin32(Size size, HWND winHandle) :
		Window(size),
		mWinHandle(winHandle)
	{
	}

	WindowWin32::~WindowWin32()
	{
	}

	void WindowWin32::ShowNativeFileDialog(FILE_DIALOG_DESC *desc)
	{
		IFileOpenDialog *openDialog;

		HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<LPVOID *>(&openDialog));
		if (SUCCEEDED(hr)) {
			openDialog->SetDefaultExtension(L"*.txt");
			openDialog->Show(NULL);
		}
	}
};