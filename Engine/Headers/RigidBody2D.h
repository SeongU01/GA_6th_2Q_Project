#pragma once
#include "Component.h"

namespace Engine
{
	class Transform;
	class Rigidbody2D : public Component
	{
	public:
		explicit Rigidbody2D(const wchar_t* name);
	private:
		virtual ~Rigidbody2D() = default;

	public:
		void Update(const float& deltaTime) override;

	public:
		void AddForce(const Vector3& force);
		void AddVelocity(const Vector3& velocity);
		
		bool IsActiveGravity() const { return _isActiveGravity; }
		Vector3 GetVelocity() const { return _velocity; }
		Vector3 GetMaxVelocity() const { return _maxVelocity; }
		void SetMass(const float& mass) { _mass = mass; }
		void SetVelocity(const Vector3& velocity) { _velocity = velocity; }
		void SetMaxVelocity(const Vector3& velocity) { _maxVelocity = velocity; }
		void SetFrictionCoefficient(const float& coefficient) { _frictionCoefficient = coefficient; }
		void SetActiveGravity(bool isActive) { _isActiveGravity = isActive; }
		void SetGravityScale(float scale) { _gravity = scale; }
		void SetAddAccel(const Vector3& accel) { _addAccel = accel; }

	public:
		__declspec(property(get = GetVelocity, put = SetVelocity)) Vector3 velocity;
		__declspec(property(get = GetMaxVelocity, put = SetMaxVelocity)) Vector3 maxVelocity;
		__declspec(property(put = SetFrictionCoefficient)) float friction;

	private:
		void Gravity(const float& deltaTime);
		// Component을(를) 통해 상속됨
		void Free() override;

	private:
		Vector3		_force{};					// 크기, 방향
		Vector3		_accel{};					// 가속도
		Vector3		_addAccel{};				// 추가가속도
		Vector3		_velocity{};				// 속도
		Vector3		_maxVelocity{};				// 최대 속도
		
		float		_mass = 1.f;				// 질량
		float		_frictionCoefficient = 1.f;	// 마찰계수
		float		_drag = 0.f;				// 공기저항
		float		_gravity = 9.8f;
		bool		_isActiveGravity = false;
	};
}

