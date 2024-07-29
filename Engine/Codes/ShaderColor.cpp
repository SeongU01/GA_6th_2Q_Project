#include "ShaderColor.h"

void Engine::ShaderColor::SetColor(float r, float g, float b, float a)
{
	_colorMatrix._11 = r;
	_colorMatrix._22 = g;
	_colorMatrix._33 = b;
	_colorMatrix._44 = a;
}

void Engine::ShaderColor::SetUseColor(float r, float g, float b, float a)
{
	D2D1_VECTOR_4F color{ r, g, b, a };
	memcpy(_colorMatrix.m[4], &color, sizeof(color));
}

void Engine::ShaderColor::ComputeShader(ID2D1Bitmap* pBitmap)
{
	_pShaderEffect->SetInput(0, pBitmap);
	_pShaderEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, (BYTE*)&_colorMatrix, sizeof(_colorMatrix));
}

void Engine::ShaderColor::Initialize(ID2D1DeviceContext* pDeviceContext)
{
	pDeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, &_pShaderEffect);

	_colorMatrix =
	{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f,
		0.f, 0.f, 0.f, 0.f
	};
}