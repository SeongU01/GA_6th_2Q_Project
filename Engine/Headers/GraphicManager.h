#pragma once
#include "Base.h"

namespace Engine
{
	class Factorys;
	class Shader;
	class GraphicManager : public Base, public SingleTon<GraphicManager>
	{
		friend class SingleTon;
	private:
		explicit GraphicManager();
		virtual ~GraphicManager() = default;
		NOCOPY(GraphicManager)

	public:
		ID2D1Factory* GetFactory() const { return _pD2DFactory; }
		IWICImagingFactory* GetWICFactory() const { return _pWICFactory; }
		IDXGIFactory4* GetDXGIFactory() const { return _pDXGIFactory; }
		IDXGIAdapter3* GetDXGIAdapter() const { return _pDXGIAdapter; }
		ID2D1DeviceContext* GetDeviceContext() const { return _pDeviceContext; }
		ID2D1HwndRenderTarget* GetRenderTarget() const { return _pRenderTarget; }
		ID2D1SolidColorBrush* GetSolidColorBrush() const { return _pSolidColorBrush; }
		IDWriteFactory* GetWriteFactory() const { return _pDWriteFactory; }
		size_t GetUsedVRAM();
		bool SetUpGraphic(HWND hWnd);

	private:
		bool Initialize();
		// Base을(를) 통해 상속됨
		void Free() override;

	private:
		ID2D1Factory*			_pD2DFactory = nullptr;
		IWICImagingFactory*		_pWICFactory = nullptr;
		IDXGIFactory4*			_pDXGIFactory = nullptr;
		IDXGIAdapter3*			_pDXGIAdapter = nullptr;
		ID2D1HwndRenderTarget*	_pRenderTarget = nullptr;
		ID2D1DeviceContext*		_pDeviceContext = nullptr;
		ID2D1SolidColorBrush*	_pSolidColorBrush = nullptr;
		IDWriteFactory*			_pDWriteFactory = nullptr;

		//ComPtr<ID3D11Device>		_pD3DDevice = nullptr;
		//ComPtr<ID3D11DeviceContext>	_pD3DContext = nullptr;
		//ComPtr<ID2D1Device>			_pD2DDevice = nullptr;
		//ComPtr<IDXGIDevice>			_pDXGIDevice = nullptr;
		//ComPtr<ID2D1DeviceContext>	_pD2DContext = nullptr;
	};
}
