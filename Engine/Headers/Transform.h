#pragma once
#include "Component.h"

namespace Engine
{
    class Transform : public Component
    {
    public:
        enum Property { Position, Direction, Scale, Rotation, Property_End };
    public:
        explicit Transform(const char* name);
    private:
        virtual ~Transform() = default;

    public:
        const D2D1_MATRIX_3X2_F& GetWorldMatrix() const { return _d2dWorldMatrix; }
        const XMFLOAT4X4& GetXMWorldMatrix() const { return _worldMatrix; }
        Vector3 GetPosition() const { return _transform[Position]; }
        Vector3 GetDirection() const { return _transform[Direction]; }
        Vector3 GetScale() const { return _transform[Scale]; }
        Transform* GetParent() { return _pParent; }

        void SetParent(Transform* parent) { _pParent = parent; }
        void SetPosition(const Vector3& position) { memcpy(&_transform[Position], &position, sizeof(Vector3)); }
        void SetDirection(const Vector3& direction) { memcpy(&_transform[Direction], &direction, sizeof(Vector3)); }
        void SetScale(const Vector3& scale) { memcpy(&_transform[Scale], &scale, sizeof(Vector3)); }
        void SetScaleSign(float x = 1.f, float y = 1.f, float z = 1.f) { _transform[Scale] *= Vector3(x, y, z); }
        void SetRotation(const Vector3& rotation) { memcpy(&_transform[Rotation], &rotation, sizeof(Vector3)); }

        void AddPosition(const Vector3& position) { _transform[Position] += position;; }
        void AddDirection(const Vector3& direction) { _transform[Direction] += direction;; }
        void AddScale(const Vector3& scale) { _transform[Scale] += scale; }
        void AddRotation(const Vector3& rotation) { _transform[Rotation] += rotation; }

    public:
        void LateUpdate(const float& deltaTime) override;

    private:
        void Free() override;

    private:
        Transform*          _pParent = nullptr;
        Vector3             _transform[Property_End];
        XMFLOAT4X4          _worldMatrix{};
        D2D1_MATRIX_3X2_F   _d2dWorldMatrix{};
    };
}