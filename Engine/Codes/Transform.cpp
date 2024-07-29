#include "Transform.h"

using namespace Engine;

Engine::Transform::Transform(const char* name)
    : Component(name)
{
    _transform[Scale] = { 1.f, 1.f, 1.f };
}

void Engine::Transform::LateUpdate(const float& deltaTime)
{
    XMMATRIX scale = XMMatrixScaling(_transform[Scale].x, _transform[Scale].y, _transform[Scale].z);
    XMMATRIX rotation = XMMatrixRotationZ(XMConvertToRadians(_transform[Rotation].z));
    XMMATRIX translation = XMMatrixTranslation(_transform[Position].x, _transform[Position].y, _transform[Position].z);

    XMMATRIX relative = scale * rotation * translation;

    if (nullptr != _pParent)
        XMStoreFloat4x4(&_worldMatrix, relative * XMLoadFloat4x4(&_pParent->_worldMatrix));
    else
        XMStoreFloat4x4(&_worldMatrix, relative);

    for (int i = 0; i < 3; i++)
        memcpy(_d2dWorldMatrix.m[i], _worldMatrix.m[i], sizeof(D2D1_VECTOR_2F));
}

void Engine::Transform::Free()
{
}