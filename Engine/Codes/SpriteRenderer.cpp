#include "SpriteRenderer.h"
#include "Transform.h"
#include "Animation.h"
#include "Texture.h"
#include "GameObject.h"
#include "GraphicManager.h"

using namespace Engine;

Engine::SpriteRenderer::SpriteRenderer(const wchar_t* name)
	: Component(name)
{
}

void Engine::SpriteRenderer::Awake()
{
	_pDeviceContext = GraphicManager::GetInstance()->GetDeviceContext();
	_pSolidColorBrush = GraphicManager::GetInstance()->GetSolidColorBrush();
	AddShader<ShaderColor>();
	AddShader<ShaderComposite>();
	SetShader<ShaderColor>();
}

void Engine::SpriteRenderer::Render()
{
	if (_isOneSelfDraw)
	{
		_oneSelfDrawFunction();
	}
	else
	{
		Draw();
	}
}

void Engine::SpriteRenderer::BindTexture(Texture* pTexture)
{
	if (nullptr == pTexture)
		return;

	_pTexture = pTexture;
	_pAnimation = nullptr;
}

void Engine::SpriteRenderer::BindAnimation(Animation* pAnimation)
{
	if (nullptr == pAnimation)
		return;

	_pAnimation = pAnimation;
	_pTexture = nullptr;
}

void Engine::SpriteRenderer::Draw()
{
	if (nullptr == _pAnimation && nullptr == _pTexture)
		return;

	ID2D1Bitmap* pBitmap = GetBitmap();

	if (nullptr == pBitmap)
		return;

	Draw(pBitmap);
}

void Engine::SpriteRenderer::Draw(ID2D1Bitmap* pBitmap)
{
	D2D1_SIZE_F size = pBitmap->GetSize();
	size.width = size.width * -0.5f + _drawOffset.x;
	size.height = size.height * -0.5f + _drawOffset.y;

	D2D1_MATRIX_3X2_F offset = D2D1::Matrix3x2F::Translation(size);
		
	_pDeviceContext->SetTransform(offset * transform.worldMatrix * gameObject._cameraMatrix);

	if (_currShader != typeid(ShaderComposite).hash_code())
		_shaderData[_currShader]->ComputeShader(pBitmap);
	_pDeviceContext->DrawImage(_shaderData[_currShader]->GetEffect());
}

void Engine::SpriteRenderer::DrawRect(const D2D1_RECT_F& rect, const D2D1::ColorF& color, float width)
{	
	_pDeviceContext->SetTransform(transform.worldMatrix * gameObject._cameraMatrix);

	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(1.f);
	_pDeviceContext->DrawRectangle(rect, _pSolidColorBrush, width);
}

void Engine::SpriteRenderer::DrawFillRect(const D2D1_RECT_F& rect, const D2D1::ColorF& color, const float& opacity)
{	
	_pDeviceContext->SetTransform(transform.worldMatrix * gameObject._cameraMatrix);

	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(opacity);
	_pDeviceContext->FillRectangle(rect, _pSolidColorBrush);
}

void Engine::SpriteRenderer::DrawLine(const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, const D2D1::ColorF& color, float strokeWidth)
{
	_pDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(1.f);
	_pDeviceContext->DrawLine(point0, point1, _pSolidColorBrush, strokeWidth);
}

void Engine::SpriteRenderer::DrawTriangle(const D2D1_POINT_2F& point0, const D2D1_POINT_2F& point1, const D2D1_POINT_2F& point2, const D2D1::ColorF& color, float opacity)
{
	ID2D1Factory* pFactory = GraphicManager::GetInstance()->GetFactory();
	ID2D1PathGeometry* pPathGeometry = nullptr;
	pFactory->CreatePathGeometry(&pPathGeometry);

	ID2D1GeometrySink* pSink = nullptr;
	pPathGeometry->Open(&pSink);

	// 삼각형의 시작 점으로 이동
	pSink->BeginFigure(point0, D2D1_FIGURE_BEGIN_FILLED);

	// 나머지 점을 통해 경로 정의
	pSink->AddLine(point1);
	pSink->AddLine(point2);

	// 경로 닫기
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pSink->Close();

	pSink->Release();

	_pDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(opacity);
	_pDeviceContext->FillGeometry(pPathGeometry, _pSolidColorBrush);
}

void Engine::SpriteRenderer::SetDrawOffset(const Vector3& offset)
{
	_drawOffset = offset;
}

void Engine::SpriteRenderer::SetOneSelfDraw(bool isActive, const std::function<void()>& function)
{
	_isOneSelfDraw = isActive;
	_oneSelfDrawFunction = function;
}

ID2D1Bitmap* Engine::SpriteRenderer::GetBitmap()
{
	ID2D1Bitmap* pBitmap = nullptr;

	if (nullptr != _pAnimation)
		pBitmap = _pAnimation->GetCurrentImage();
	else
		pBitmap = _pTexture->GetImage(_index);

	return pBitmap;
}

void Engine::SpriteRenderer::Free()
{
	for (auto& shader : _shaderData)
		SafeRelease(shader.second);
}