#include "WinApp.h"

using namespace Engine;



void Engine::WinApp::Free()
{
}

bool WinApp::Initialize(HINSTANCE hInstance, const TCHAR* appName, int width, int height)
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
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = appName;

	RegisterClass(&wndClass);	

	RECT rect{ _startLeft, _startTop, _startLeft + width, _startTop + height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	int adjustedWidth = rect.right - rect.left;
	int adjustedHeight = rect.bottom - rect.top;

	_hInstance = hInstance;
	_hWnd = CreateWindow(appName, appName, WS_OVERLAPPED | WS_SYSMENU,
		_startLeft, _startTop, adjustedWidth, adjustedHeight, NULL, NULL, hInstance, NULL);

	if (!_hWnd)
		return false;

	ShowWindow(_hWnd, SW_NORMAL);
	UpdateWindow(_hWnd);

	return true;
}

WinApp* Engine::WinApp::Create(HINSTANCE hInstance, const TCHAR* appName, int width, int height)
{
	WinApp* pInstance = new WinApp;

	if (pInstance->Initialize(hInstance, appName, width, height))
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