#include "SpriteRenderer.h"
#include "Transform.h"
#include "Animation.h"
#include "Texture.h"
#include "GraphicManager.h"

using namespace Engine;

Engine::SpriteRenderer::SpriteRenderer(const char* name)
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
	Draw();
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

	if (_notAffectCamera)
		_pDeviceContext->SetTransform(offset * _pTransform->worldMatrix);
	else
		_pDeviceContext->SetTransform(offset * _pTransform->worldMatrix * _cameraMatrix);

	if (_currShader != typeid(ShaderComposite).hash_code())
		_shaderData[_currShader]->ComputeShader(pBitmap);
	_pDeviceContext->DrawImage(_shaderData[_currShader]->GetEffect());
}

void Engine::SpriteRenderer::DrawRect(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color)
{
	_pDeviceContext->SetTransform(_cameraMatrix);
	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(1.f);
	_pDeviceContext->DrawRectangle(rect, _pSolidColorBrush);
}

void Engine::SpriteRenderer::DrawFillRect(const D2D1_RECT_F& rect, const D2D1_COLOR_F& color, const float& opacity)
{
	_pDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(opacity);
	_pDeviceContext->FillRectangle(rect, _pSolidColorBrush);
}

void Engine::SpriteRenderer::SetDrawOffset(const Vector3& offset)
{
	_drawOffset = offset;
}

void Engine::SpriteRenderer::NotAffectCamera()
{
	_notAffectCamera = true;
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