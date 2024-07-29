#pragma once
#include "Component.h"

namespace Engine
{
	class TextRenderer : public Engine::Component
	{
	public:
		explicit TextRenderer(const char* name) { _name = name; }
	private:
		virtual ~TextRenderer() = default;

	public:
		void Start() override;
		void Render() override;

	public:
		void SetFontColor(D2D1::ColorF::Enum color) { _color = color; }
		void SetFontSize(float size) { _fontSize = size; }
		void SetText(const wchar_t* text) { _text = text; }
		void SetDrawRect(const D2D1_RECT_F& drawRect) { _drawRect = drawRect; }
		void SetFontWeight(DWRITE_FONT_WEIGHT fontWeight) { _fontWeight = fontWeight; }

	private:
		// Component을(를) 통해 상속됨
		void Free() override;

	private:
		D2D1_RECT_F				_drawRect;
		IDWriteTextFormat*		_pWriteTextFormat = nullptr;
		ID2D1SolidColorBrush*	_pSolidColorBrush = nullptr;
		ID2D1DeviceContext*		_pDeviceContext = nullptr;

		const wchar_t*			_text = nullptr;
		float					_fontSize = 20.f;		
		D2D1::ColorF::Enum      _color = D2D1::ColorF::White;
		DWRITE_FONT_WEIGHT		_fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	};
}