#include "ShaderComposite.h"

void Engine::ShaderComposite::CompositeShader(ID2D1Effect* pEffect1, ID2D1Effect* pEffect2)
{
    _pShaderEffect->SetInputEffect(0, pEffect1);
    _pShaderEffect->SetInputEffect(1, pEffect2);
    _pShaderEffect->SetValue(D2D1_COMPOSITE_PROP_MODE, D2D1_COMPOSITE_MODE_PLUS);
}

void Engine::ShaderComposite::ComputeShader(ID2D1Bitmap* pBitmap)
{
    _pShaderEffect->SetInput(2, pBitmap);
}

void Engine::ShaderComposite::Initialize(ID2D1DeviceContext* pDeviceContext)
{
    pDeviceContext->CreateEffect(CLSID_D2D1Composite, &_pShaderEffect);
}
