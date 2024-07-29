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
		void LateUpdate(const float& deltaTime) override;

	public:
		void AddForce(const XMFLOAT2& force);
		void AddVelocity(const XMFLOAT2& velocity);
		
		bool IsActiveGravity() const;
		XMFLOAT2 GetVelocity() const;
		XMFLOAT2 GetMaxVelocity() const;
		void SetTransform(Transform* pTransform);
		void SetMass(const float& mass);
		void SetVelocity(const XMFLOAT2& velocity);
		void SetMaxVelocity(const XMFLOAT2& velocity);
		void SetFrictionCoefficient(const float& coefficient);
		void SetActiveGravity(bool isActive);
		void SetGravityScale(float scale);
		void SetAddAccel(const XMFLOAT2& accel);


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
		float		_gravity = 9.8f;
		bool		_isActiveGravity = false;
	};
}

