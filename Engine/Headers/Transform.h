#pragma once
#include "Component.h"

namespace Engine
{
    class Transform : public Component
    {
    public:
        enum Property { Position, Direction, Scale, Rotation, Property_End };
    public:
        explicit Transform(const wchar_t* name);
    private:
        virtual ~Transform() = default;

    public:
        const D2D1_MATRIX_3X2_F& GetWorldMatrix() const { return _d2dWorldMatrix; }
        const XMFLOAT4X4& GetXMWorldMatrix() const { return _worldMatrix; }
        Vector3 GetPosition() const { return _transform[Position]; };
        Vector3 GetDirection() const { return _transform[Direction]; }
        Vector3 GetScale() const { return _transform[Scale]; }
        Vector3 GetRotation() const { return _transform[Rotation]; }
        Vector3 GetWorldPosition() const;
        Transform* GetParent() { return _pParent; }

        void SetParent(Transform* parent) { _pParent = parent; }
        void SetPosition(const Vector3& position) { memcpy(&_transform[Position], &position, sizeof(Vector3)); }
        void SetPosition(const XMVECTOR& position) { _transform[Position] = position; }
        void SetDirection(const Vector3& direction) { memcpy(&_transform[Direction], &direction, sizeof(Vector3)); }
        void SetScale(const Vector3& scale) { memcpy(&_transform[Scale], &scale, sizeof(Vector3)); }
        void SetScaleSign(float x = 1.f, float y = 1.f, float z = 1.f) { _transform[Scale] *= Vector3(x, y, z); }
        void SetRotation(const Vector3& rotation) { memcpy(&_transform[Rotation], &rotation, sizeof(Vector3)); }
        
    public:
        __declspec(property(get = GetPosition, put = SetPosition)) Vector3 position;
        __declspec(property(get = GetDirection, put = SetDirection)) Vector3 direction;
        __declspec(property(get = GetRotation, put = SetRotation)) Vector3 rotation;
        __declspec(property(get = GetScale, put = SetScale)) Vector3 scale;
        __declspec(property(get = GetWorldMatrix)) D2D1_MATRIX_3X2_F worldMatrix;
        __declspec(property(get = GetXMWorldMatrix)) XMFLOAT4X4 xmWorldMatrix;

    public:
        void UpdateTransform();

    private:
        void Free() override;

    private:
        Transform*          _pParent = nullptr;
        Vector3             _transform[Property_End];
        XMFLOAT4X4          _worldMatrix{};
        D2D1_MATRIX_3X2_F   _d2dWorldMatrix{};
    };
}