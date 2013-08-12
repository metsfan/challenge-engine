#pragma once

#ifdef WINDOWS

// Windows Header Files:
#include <windows.h>
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

// DirectX Header Files
#include <D3D11.h>
#include <D3DX11.h>

#include <Engine/GameApplicationWindows.h>
#include <Engine/Disk/Platform/Windows/AssetLoaderWindows.h>

#endif