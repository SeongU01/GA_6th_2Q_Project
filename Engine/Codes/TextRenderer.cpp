#include "TextRenderer.h"
#include "GraphicManager.h"

using namespace Engine;

Engine::TextRenderer::TextRenderer(const wchar_t* name, D2D1::ColorF color, float size, DWRITE_FONT_WEIGHT fontWeight)
	: Component(name), _color(color), _fontSize(size), _fontWeight(fontWeight)
{	
	GraphicManager* pGraphicMgr = GraphicManager::GetInstance();
	_pSolidColorBrush = pGraphicMgr->GetSolidColorBrush();
	_pDeviceContext = pGraphicMgr->GetDeviceContext();
	_pWriteFactory = pGraphicMgr->GetWriteFactory();

	_pWriteFactory->CreateTextFormat(
		L"¸¼Àº °íµñ", NULL,
		_fontWeight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		_fontSize, L"", &_pWriteTextFormat);
}

void TextRenderer::Render()
{
	if (nullptr == _pDeviceContext)
		return;	
	
	const D2D1_MATRIX_3X2_F& offset = D2D1::Matrix3x2F::Translation(_offset.x, _offset.y);

	if (_notAffectCamera)
		_pDeviceContext->SetTransform(offset * transform.worldMatrix);
	else
		_pDeviceContext->SetTransform(offset * transform.worldMatrix * gameObject._cameraMatrix);

	_pSolidColorBrush->SetColor(_color);
	_pSolidColorBrush->SetOpacity(1.f);

	if (nullptr != _pWriteTextLayout)
	{
		_pDeviceContext->DrawTextLayout(_drawPoint, _pWriteTextLayout, _pSolidColorBrush);
	}
	else
	{		
		_pDeviceContext->DrawText(_text.c_str(), (UINT32)_text.length(), _pWriteTextFormat, _drawRect, _pSolidColorBrush);
	}
}

void Engine::TextRenderer::SetDrawRect(float width, float height)
{
	_drawRect = { 0.f, 0.f, width, height };
	_drawPoint = { width, height };
}

void Engine::TextRenderer::SetTextLayout(const wchar_t* text, float width, float height)
{
	_pWriteFactory->CreateTextLayout(text, lstrlen(text), _pWriteTextFormat, width, height, &_pWriteTextLayout);
}

void Engine::TextRenderer::SetTextRangeEffectColor(unsigned int start, unsigned int length, D2D1::ColorF color)
{	
	if (nullptr == _pWriteTextLayout)
		return;

	ID2D1SolidColorBrush* pSolidColorBrush = nullptr;

	_pDeviceContext->CreateSolidColorBrush(color, &pSolidColorBrush);
	DWRITE_TEXT_RANGE textRange = { start, length };
	_pWriteTextLayout->SetDrawingEffect(pSolidColorBrush, textRange);
	_colorBrushs.push_back(pSolidColorBrush);
}

void Engine::TextRenderer::SetTextRangeEffectBold(unsigned int start, unsigned int length)
{
	if (nullptr == _pWriteTextLayout)
		return;
	
	DWRITE_TEXT_RANGE textRange = { start, length };
	_pWriteTextLayout->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD, textRange);
}

void Engine::TextRenderer::SetTextRangeEffectUnderline(unsigned int start, unsigned int length)
{
	if (nullptr == _pWriteTextLayout)
		return;

	DWRITE_TEXT_RANGE textRange = { start, length };
	_pWriteTextLayout->SetUnderline(TRUE, textRange);
}

void Engine::TextRenderer::SetTextRangeEffectFontFamily(unsigned int start, unsigned int length, const wchar_t* fontFamily)
{
	DWRITE_TEXT_RANGE textRange = { start, length };
	_pWriteTextLayout->SetFontFamilyName(fontFamily, textRange);
}

void Engine::TextRenderer::SetTextAlignment(DWRITE_TEXT_ALIGNMENT alignment)
{
	_pWriteTextFormat->SetTextAlignment(alignment);
}

void Engine::TextRenderer::SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT alignment)
{
	_pWriteTextFormat->SetParagraphAlignment(alignment);
}

void TextRenderer::Free()
{
	for (auto& brush : _colorBrushs)
		SafeRelease(brush);

	SafeRelease(_pWriteTextFormat);
}
