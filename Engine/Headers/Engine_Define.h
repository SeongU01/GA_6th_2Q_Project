#pragma once

// 여기에 미리 컴파일하려는 헤더 추가
#include <iostream>
#include <Windows.h>
#include <io.h>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <functional>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <thread>
#include <mutex>
#include <random>
#include <iomanip>

#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1helper.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"windowscodecs.lib")

using namespace DirectX;

#include "Engine_Macro.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"
#include "Engine_Function.h"
#include "Engine_Enum.h"
