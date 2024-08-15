#include "Transform.h"

using namespace Engine;

Engine::Transform::Transform(const wchar_t* name)
    : Component(name)
{
    _transform[Scale] = { 1.f, 1.f, 1.f };
}

Vector3 Engine::Transform::GetWorldPosition() const
{
    Vector3 position{};
    memcpy(&position, _worldMatrix.m[3], sizeof(Vector3));

    return position;
}

void Engine::Transform::UpdateTransform()
{
    XMMATRIX scale = XMMatrixScaling(_transform[Scale].x, _transform[Scale].y, _transform[Scale].z);
    XMMATRIX rotation = XMMatrixRotationZ(XMConvertToRadians(_transform[Rotation].z));
    XMMATRIX translation = XMMatrixTranslation(_transform[Position].x, _transform[Position].y, _transform[Position].z);

    XMMATRIX relative = scale * rotation * translation;

    if (nullptr != _pParent)
        XMStoreFloat4x4(&_worldMatrix, relative * XMLoadFloat4x4(&_pParent->_worldMatrix));
    else
        XMStoreFloat4x4(&_worldMatrix, relative);

    memcpy(_d2dWorldMatrix.m[0], _worldMatrix.m[0], sizeof(D2D1_VECTOR_2F));
    memcpy(_d2dWorldMatrix.m[1], _worldMatrix.m[1], sizeof(D2D1_VECTOR_2F));
    memcpy(_d2dWorldMatrix.m[2], _worldMatrix.m[3], sizeof(D2D1_VECTOR_2F));
}

void Engine::Transform::Free()
{
}