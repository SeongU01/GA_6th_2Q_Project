#include "GraphicManager.h"
#include "ShaderComposite.h"
#include "ShaderColor.h"
#include "ShaderMotionBlur.h"

using namespace Engine;

Engine::GraphicManager::GraphicManager()
{
	Initialize();
}

size_t Engine::GraphicManager::GetUsedVRAM()
{
	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	_pDXGIAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);
	return videoMemoryInfo.CurrentUsage / 1024 / 1024;
}

bool Engine::GraphicManager::SetUpGraphic(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	if (FAILED(_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&_pRenderTarget)))
	{
		return false;
	}

	if (FAILED(_pRenderTarget->QueryInterface(
		__uuidof(ID2D1DeviceContext),
		reinterpret_cast<void**>(&_pDeviceContext))))
	{
		return false;
	}

	if (FAILED(_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Lime), &_pSolidColorBrush)))
	{
		return false;
	}

	return true;
}

bool Engine::GraphicManager::Initialize()
{
	if (FAILED(CoInitialize(nullptr)))
		return false;

	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &_pD2DFactory)))
		return false;

	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pWICFactory))))
		return false;

	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&_pDXGIFactory)))
		return false;

	if (FAILED(_pDXGIFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&_pDXGIAdapter))))
		return false;
	
	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(_pDWriteFactory), reinterpret_cast<IUnknown**>(&_pDWriteFactory))))
		return false;

	return true;
}

void Engine::GraphicManager::Free()
{
	SafeRelease(_pDWriteFactory);
	SafeRelease(_pSolidColorBrush);
	SafeRelease(_pDeviceContext);
	SafeRelease(_pRenderTarget);
	SafeRelease(_pDXGIFactory);
	SafeRelease(_pDXGIAdapter);
	SafeRelease(_pWICFactory);
	SafeRelease(_pD2DFactory);
	CoUninitialize();
}
