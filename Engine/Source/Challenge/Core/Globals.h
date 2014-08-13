#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>
#include <Shobjidl.h>

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
#include <algorithm>
#include <locale>

// GLM Libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/epsilon.hpp>

#include <Poco/JSON/Parser.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

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

using Poco::UUID;

static UUID UUIDZero;

#define RandomUUID() (Poco::UUIDGenerator::defaultGenerator().createRandom())

