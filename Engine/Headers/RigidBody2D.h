#pragma once
#include "Component.h"

namespace Engine
{
	class Transform;
	class Rigidbody2D : public Component
	{
	public:
		explicit Rigidbody2D(const char* name);
	private:
		virtual ~Rigidbody2D() = default;

	public:
		void Update(const float& deltaTime) override;

	public:
		void AddForce(const XMFLOAT2& force);
		void AddVelocity(const XMFLOAT2& velocity);
		
		bool IsActiveGravity() const { return _isActiveGravity; }
		XMFLOAT2 GetVelocity() const { return _velocity; }
		XMFLOAT2 GetMaxVelocity() const { return _maxVelocity; }
		void SetTransform(Transform* pTransform) { _pTransform = pTransform; }
		void SetMass(const float& mass) { _mass = mass; }
		void SetVelocity(const XMFLOAT2& velocity) { _velocity = velocity; }
		void SetMaxVelocity(const XMFLOAT2& velocity) { _maxVelocity = velocity; }
		void SetFrictionCoefficient(const float& coefficient) { _frictionCoefficient = coefficient; }
		void SetActiveGravity(bool isActive) { _isActiveGravity = isActive; }
		void SetGravityScale(float scale) { _gravity = scale; }
		void SetAddAccel(const XMFLOAT2& accel) { _addAccel = accel; }

	public:
		__declspec(property(get = GetVelocity, put = SetVelocity)) XMFLOAT2 velocity;
		__declspec(property(get = GetMaxVelocity, put = SetMaxVelocity)) XMFLOAT2 maxVelocity;
		__declspec(property(put = SetFrictionCoefficient)) float friction;

	private:
		void Gravity(const float& deltaTime);
		// Component을(를) 통해 상속됨
		void Free() override;

	private:
		Transform*	_pTransform = nullptr;
		XMFLOAT2	_force{};					// 크기, 방향
		XMFLOAT2	_accel{};					// 가속도
		XMFLOAT2	_addAccel{};				// 추가가속도
		XMFLOAT2	_velocity{};				// 속도
		XMFLOAT2	_maxVelocity{};				// 최대 속도
		
		float		_mass = 1.f;				// 질량
		float		_frictionCoefficient = 1.f;	// 마찰계수
		float		_drag = 0.f;				// 공기저항
		float		_gravity = 9.8f;
		bool		_isActiveGravity = false;
	};
}

