#include "ShaderGaussianBluer.h"

void Engine::ShaderGaussianBluer::ComputeShader(ID2D1Bitmap* pBitmap)
{
	_pShaderEffect->SetInput(0, pBitmap);
	_pShaderEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, _value);
}

void Engine::ShaderGaussianBluer::Initialize(ID2D1DeviceContext* pDeviceContext)
{
	pDeviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &_pShaderEffect);
}
