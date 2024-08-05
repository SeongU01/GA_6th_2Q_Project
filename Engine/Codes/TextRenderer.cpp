#include "TextRenderer.h"
#include "GraphicManager.h"

using namespace Engine;

Engine::TextRenderer::TextRenderer(const char* name, D2D1::ColorF color, float size, DWRITE_FONT_WEIGHT fontWeight)
	: Component(name), _color(color), _fontSize(size), _fontWeight(fontWeight)
{	
	GraphicManager* pGraphicMgr = GraphicManager::GetInstance();
	_pSolidColorBrush = pGraphicMgr->GetSolidColorBrush();
	_pDeviceContext = pGraphicMgr->GetDeviceContext();
	_pWriteFactory = pGraphicMgr->GetWriteFactory();

	_pWriteFactory->CreateTextFormat(
		L"맑은 고딕", NULL,
		_fontWeight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		_fontSize, L"", &_pWriteTextFormat);

	// 텍스트를 수평 및 수직으로 중앙에 맞춥니다.
	_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void TextRenderer::Render()
{
	if (nullptr == _pDeviceContext)
		return;	

	_pDeviceContext->SetTransform(transform->worldMatrix);
	_pSolidColorBrush->SetColor(_color);
	_pSolidColorBrush->SetOpacity(1.f);

	if (nullptr != _pWriteTextLayout)
	{
		_pDeviceContext->DrawTextLayout(_drawPoint, _pWriteTextLayout, _pSolidColorBrush);
	}
	else
	{		
		_pDeviceContext->DrawText(_text, lstrlen(_text), _pWriteTextFormat, _drawRect, _pSolidColorBrush);
	}

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

void TextRenderer::Free()
{
	for (auto& brush : _colorBrushs)
		SafeRelease(brush);

	SafeRelease(_pWriteTextFormat);
}
