#pragma once

// ���⿡ �̸� �������Ϸ��� ��� �߰�
#include <iostream>
#include <Windows.h>
#include <io.h>

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <thread>
#include <mutex>

//#include <DirectXTex.h>
//#include <d3d11.h>
//#include <wrl/client.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1helper.h>
//#include <dxgi1_2.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>

#pragma comment(lib,"d2d1.lib")
//#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"windowscodecs.lib")
//#pragma comment(lib, "DirectXTex.lib")

#include "Engine_Function.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"
#include "Engine_Enum.h"

using namespace DirectX;