#include "ShaderMotionBlur.h"

void Engine::ShaderMotionBlur::ComputeShader(ID2D1Bitmap* pBitmap)
{
	_pShaderEffect->SetInput(0, pBitmap);
	_pShaderEffect->SetValue(D2D1_DIRECTIONALBLUR_PROP_STANDARD_DEVIATION, _value);
}

void Engine::ShaderMotionBlur::Initialize(ID2D1DeviceContext* pDeviceContext)
{
	pDeviceContext->CreateEffect(CLSID_D2D1DirectionalBlur, &_pShaderEffect);
}
