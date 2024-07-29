#include "TextRenderer.h"
#include "GraphicManager.h"

using namespace Engine;

void TextRenderer::Start()
{
	GraphicManager* pGraphicMgr = GraphicManager::GetInstance();
	_pSolidColorBrush = pGraphicMgr->GetSolidColorBrush();
	_pDeviceContext = pGraphicMgr->GetDeviceContext();

	pGraphicMgr->GetWriteFactory()->CreateTextFormat(
		L"���� ���", NULL,
		_fontWeight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		_fontSize, L"", &_pWriteTextFormat);

	// �ؽ�Ʈ�� ���� �� �������� �߾ӿ� ����ϴ�.
	_pWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	_pWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void TextRenderer::Render()
{
	if (nullptr == _pDeviceContext)
		return;

	_pDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	_pSolidColorBrush->SetColor(D2D1::ColorF(_color));
	_pSolidColorBrush->SetOpacity(1.f);
	_pDeviceContext->DrawText(_text, lstrlen(_text), _pWriteTextFormat, _drawRect, _pSolidColorBrush);
}

void TextRenderer::Free()
{
	SafeRelease(_pWriteTextFormat);
}
