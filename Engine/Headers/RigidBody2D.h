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
		void Initialize() override;
		void Update(const float& deltaTime) override;

	public:
		void AddForce(const Vector3& force);
		void AddVelocity(const Vector3& velocity);
		
		bool IsActiveGravity() const { return _isActiveGravity; }
		Vector3 GetVelocity() const { return _velocity; }
		Vector3 GetMaxVelocity() const { return _maxVelocity; }
		void SetTransform(Transform* pTransform) { _pTransform = pTransform; }
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
		// Component��(��) ���� ��ӵ�
		void Free() override;

	private:
		Transform*	_pTransform = nullptr;
		Vector3		_force{};					// ũ��, ����
		Vector3		_accel{};					// ���ӵ�
		Vector3		_addAccel{};				// �߰����ӵ�
		Vector3		_velocity{};				// �ӵ�
		Vector3		_maxVelocity{};				// �ִ� �ӵ�
		
		float		_mass = 1.f;				// ����
		float		_frictionCoefficient = 1.f;	// �������
		float		_drag = 0.f;				// ��������
		float		_gravity = 9.8f;
		bool		_isActiveGravity = false;
	};
}

