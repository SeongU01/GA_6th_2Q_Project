#pragma once
#include "Base.h"

namespace Engine
{
	class WinApp : public Base
	{
	private:
		explicit WinApp() = default;
		virtual ~WinApp() = default;

	public:
		HINSTANCE GetInstance() const { return _hInstance; }
		HWND GetWindow() const { return _hWnd; }
		const int GetWidth() const { return _width; }
		const int GetHeight() const { return _height; }
		void RestoreDisplay();

	private:
		void SaveCurrentResolution();
		static void ChangeResolution(int width, int height);
		bool Initialize(HINSTANCE hInstance, const TCHAR* appName, int width, int height, bool isFullScreen);
		// Base을(를) 통해 상속됨
		void Free() override;

	public:
		static WinApp* Create(HINSTANCE hInstance, const TCHAR* appName, int width, int height, bool isFullScreen = false);
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE	_hInstance = nullptr;
		HWND		_hWnd = nullptr;
		int			_width = 0;
		int			_height = 0;		

		const int _startLeft = 100;
		const int _startTop = 100;
	};
}