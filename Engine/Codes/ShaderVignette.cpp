#include "ShaderVignette.h"
#include <d2d1effects_2.h>

void Engine::ShaderVignette::SetValue(const D2D1_VECTOR_4F& color, float transitionSize, float strength)
{
	_color = color;
	_transitionSize = transitionSize;
	_strength = strength;
}

void Engine::ShaderVignette::ComputeShader(ID2D1Bitmap* pBitmap)
{
	_pShaderEffect->SetInput(0, pBitmap);
	_pShaderEffect->SetValue(D2D1_VIGNETTE_PROP_COLOR, _color);
	_pShaderEffect->SetValue(D2D1_VIGNETTE_PROP_TRANSITION_SIZE, _transitionSize);
	_pShaderEffect->SetValue(D2D1_VIGNETTE_PROP_STRENGTH, _strength);
}

void Engine::ShaderVignette::Initialize(ID2D1DeviceContext* pDeviceContext)
{
	pDeviceContext->CreateEffect(CLSID_D2D1Vignette, &_pShaderEffect);
}