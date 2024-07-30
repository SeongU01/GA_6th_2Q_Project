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
		// Component��(��) ���� ��ӵ�
		void Free() override;

	private:
		Transform*	_pTransform = nullptr;
		XMFLOAT2	_force{};					// ũ��, ����
		XMFLOAT2	_accel{};					// ���ӵ�
		XMFLOAT2	_addAccel{};				// �߰����ӵ�
		XMFLOAT2	_velocity{};				// �ӵ�
		XMFLOAT2	_maxVelocity{};				// �ִ� �ӵ�
		
		float		_mass = 1.f;				// ����
		float		_frictionCoefficient = 1.f;	// �������
		float		_drag = 0.f;				// ��������
		float		_gravity = 9.8f;
		bool		_isActiveGravity = false;
	};
}

