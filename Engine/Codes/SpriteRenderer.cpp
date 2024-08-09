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

	const D2D1_MATRIX_3X2_F& offset = D2D1::Matrix3x2F::Translation(size);
	
	if (_notAffectCamera)
		_pDeviceContext->SetTransform(offset * transform.worldMatrix);
	else
		_pDeviceContext->SetTransform(offset * transform.worldMatrix * gameObject._cameraMatrix);

	if (_currShader != typeid(ShaderComposite).hash_code())
		_shaderData[_currShader]->ComputeShader(pBitmap);
	_pDeviceContext->DrawImage(_shaderData[_currShader]->GetEffect());
}

void Engine::SpriteRenderer::DrawRect(const D2D1_RECT_F& rect, const D2D1::ColorF& color, float width)
{
	if (_notAffectCamera)
		_pDeviceContext->SetTransform(transform.worldMatrix);
	else
		_pDeviceContext->SetTransform(transform.worldMatrix * gameObject._cameraMatrix);

	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(1.f);
	_pDeviceContext->DrawRectangle(rect, _pSolidColorBrush, width);
}

void Engine::SpriteRenderer::DrawFillRect(const D2D1_RECT_F& rect, const D2D1::ColorF& color, const float& opacity)
{
	if (_notAffectCamera)
		_pDeviceContext->SetTransform(transform.worldMatrix);
	else
		_pDeviceContext->SetTransform(transform.worldMatrix * gameObject._cameraMatrix);

	_pSolidColorBrush->SetColor(color);
	_pSolidColorBrush->SetOpacity(opacity);
	_pDeviceContext->FillRectangle(rect, _pSolidColorBrush);
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