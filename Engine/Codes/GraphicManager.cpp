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
	
	//D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	//D3D_FEATURE_LEVEL featureLevel;
	//HRESULT hr = D3D11CreateDevice(
	//	nullptr,
	//	D3D_DRIVER_TYPE_HARDWARE,
	//	nullptr,
	//	D3D11_CREATE_DEVICE_BGRA_SUPPORT,
	//	featureLevels,
	//	ARRAYSIZE(featureLevels),
	//	D3D11_SDK_VERSION,
	//	&_pD3DDevice,
	//	&featureLevel,
	//	&_pD3DContext);
	//if (FAILED(hr)) {
	//	// 오류 처리
	//}

	//// IDXGIDevice를 얻어옵니다
	//hr = _pD3DDevice.As(&_pDXGIDevice);

	//if (FAILED(hr)) {
	//	// 오류 처리
	//}

	//ScratchImage image;
	//hr = LoadFromDDSFile(L"01.dds", DDS_FLAGS_NONE, nullptr, image);
	//if (FAILED(hr)) {
	//	// 오류 처리
	//}

	//ComPtr<ID3D11Resource> resource;
	//hr = CreateTexture(_pD3DDevice.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), &resource);
	//if (FAILED(hr)) {
	//	// 오류 처리
	//}
	//
	//ComPtr<ID3D11Texture2D> texture;
	//hr = resource.As(&texture);

	//ComPtr<IDXGISurface> dxgiSurface;
	//hr = texture.As(&dxgiSurface);
	//if (FAILED(hr)) {
	//	// 오류 처리
	//}

	//D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
	//	D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
	//	D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

	//ComPtr<ID2D1Bitmap1> d2dBitmap;
	//hr = _pDeviceContext->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bitmapProperties, &d2dBitmap);
	//if (FAILED(hr))
	//{
	//}

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
