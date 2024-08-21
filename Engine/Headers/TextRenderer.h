#pragma once
#include "Component.h"

namespace Engine
{
	class TextRenderer : public Engine::Component
	{
	public:
		explicit TextRenderer(const wchar_t* name, D2D1::ColorF color = D2D1::ColorF::White, float size = 25.f, DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL);
	private:
		virtual ~TextRenderer() = default;

	public:
		void Render() override;

	public:		
		void SetText(const wchar_t* text) {_text = text; }
		void SetDrawRect(float width, float height);
		void SetOffset(const Vector3& offset) { _offset = offset; }
		void SetTextLayout(const wchar_t* text, float width, float height);
		void SetTextRangeEffectColor(unsigned int start, unsigned int length, D2D1::ColorF color);
		void SetTextRangeEffectBold(unsigned int start, unsigned int length);
		void SetTextRangeEffectUnderline(unsigned int start, unsigned int length);
		void SetTextRangeEffectFontFamily(unsigned int start, unsigned int length, const wchar_t* fontFamily);
		void SetTextAlignment(DWRITE_TEXT_ALIGNMENT alignment);
		void SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT alignment);
		void SetNotAffectCamera(bool isActive) { _notAffectCamera = isActive; }

	private:
		// Component을(를) 통해 상속됨
		void Free() override;

	private:
		std::list<ID2D1SolidColorBrush*>	_colorBrushs;
		D2D1_RECT_F							_drawRect{};
		D2D1_POINT_2F						_drawPoint{};
		IDWriteTextFormat*					_pWriteTextFormat = nullptr;
		ID2D1SolidColorBrush*				_pSolidColorBrush = nullptr;
		ID2D1DeviceContext*					_pDeviceContext = nullptr;
		IDWriteTextLayout*					_pWriteTextLayout = nullptr;
		IDWriteFactory*						_pWriteFactory = nullptr;

		D2D1::ColorF						_color = D2D1::ColorF::White;
		Vector3								_offset{};
		std::wstring						_text;
		float								_fontSize = 20.f;		
		DWRITE_FONT_WEIGHT					_fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
		bool								_notAffectCamera = false;
	};
}