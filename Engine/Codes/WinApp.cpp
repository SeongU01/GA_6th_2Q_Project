#include "WinApp.h"
using namespace Engine;

DEVMODE		_originalDevMode{};

void Engine::WinApp::Free()
{
}

void Engine::WinApp::RestoreDisplay()
{
	ChangeResolution(_originalDevMode.dmPelsWidth, _originalDevMode.dmPelsHeight);
}

void Engine::WinApp::SaveCurrentResolution()
{
	_originalDevMode.dmSize = sizeof(_originalDevMode);

	if (!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &_originalDevMode))
	{
		std::cerr << "Failed to get current resolution" << std::endl;
	}
}

void Engine::WinApp::ChangeResolution(int width, int height)
{
	DEVMODE devMode;
	ZeroMemory(&devMode, sizeof(devMode));
	devMode.dmSize = sizeof(devMode);
	devMode.dmPelsWidth = width;
	devMode.dmPelsHeight = height;
	devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	LONG result = ChangeDisplaySettings(&devMode, 0);
	if (result != DISP_CHANGE_SUCCESSFUL)
	{
		std::cerr << "Failed to change resolution" << std::endl;
	}
}

bool WinApp::Initialize(HINSTANCE hInstance, const TCHAR* appName, int width, int height, bool isFullScreen)
{
	_width = width;
	_height = height;

	WNDCLASS wndClass;

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursorFromFile(TEXT("../Resources/Cursor/black.cur"));
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);

	if (isFullScreen)
	{
		SaveCurrentResolution();
		ChangeResolution(_width, _height);
	}

	RECT rect{ _startLeft, _startTop, _startLeft + width, _startTop + height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	int adjustedWidth = rect.right - rect.left;
	int adjustedHeight = rect.bottom - rect.top;

	_hInstance = hInstance;

	if (isFullScreen)
	{
		_hWnd = CreateWindow(appName, appName, WS_POPUP | WS_SYSMENU,
			_startLeft, _startTop, adjustedWidth, adjustedHeight, NULL, NULL, hInstance, NULL);

		if (!_hWnd)
			return false;

		ShowWindow(_hWnd, SW_MAXIMIZE);
	}
	else
	{
		_hWnd = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
			_startLeft, _startTop, adjustedWidth, adjustedHeight, NULL, NULL, hInstance, NULL);

		if (!_hWnd)
			return false;

		ShowWindow(_hWnd, SW_NORMAL);
	}

	UpdateWindow(_hWnd);

	return true;
}

WinApp* Engine::WinApp::Create(HINSTANCE hInstance, const TCHAR* appName, int width, int height, bool isFullScreen)
{
	WinApp* pInstance = new WinApp;

	if (pInstance->Initialize(hInstance, appName, width, height, isFullScreen))
		return pInstance;

	SafeRelease(pInstance);
	return nullptr;
}

LRESULT CALLBACK WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}