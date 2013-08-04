#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

// DirectX Header Files
#include <D3D11.h>
#include <D3DX11.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3dcompiler.lib")

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <Rpc.h>

// STL Libraries
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <memory>
#include <list>
#include <thread>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <mutex>

// Boost libraries
#include <boost/optional/optional.hpp>

// GLM Libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define ROOT_DIR "C:/gamedev/dungeon-raider/DungeonRaider/DungeonRaider/Source"
#define GUID_SIZE 36
#define CURL_STATICLIB 1

// Macros
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

const double kPi = 3.14159265;
const int kInfinity = 99999999;
const float DEG2RAD = 3.14159/180;

// Custom typedefs
typedef std::string ActorType;
typedef std::string ActorId;
typedef float real;
