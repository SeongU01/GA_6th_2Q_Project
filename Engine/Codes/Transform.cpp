#include "Transform.h"

using namespace Engine;

Engine::Transform::Transform(const char* name)
{
    _name = name;
    _transform[Scale] = { 1.f, 1.f, 1.f };
}

Vector3 Engine::Transform::TransformCoordByMyWorldMatrix(const Vector3& v)
{    
    return Vector3(v.x * _worldMatrix._11 + v.y * _worldMatrix._21 + _worldMatrix._31,
                   v.x * _worldMatrix._12 + v.y * _worldMatrix._22 + _worldMatrix._32,
                   0.f);
}

void Engine::Transform::Update(const float& deltaTime)
{
    D2D1_MATRIX_3X2_F scale = D2D1::Matrix3x2F::Scale(_transform[Scale].x, _transform[Scale].y);
    D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(_transform[Rotation].z);
    D2D1_MATRIX_3X2_F translation = D2D1::Matrix3x2F::Translation(_transform[Position].x, _transform[Position].y);

    D2D1_MATRIX_3X2_F relative = scale * rotation * translation;

    if (nullptr != _pParent)
        _worldMatrix = relative * _pParent->_worldMatrix;
    else
        _worldMatrix = relative;
}

void Engine::Transform::Free()
{
}