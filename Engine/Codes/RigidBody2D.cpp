#include "Rigidbody2D.h"
#include "Transform.h"

using namespace Engine;

Engine::Rigidbody2D::Rigidbody2D(const char* name)
	: Component(name), _maxVelocity(XMFLOAT2(1000.f, 1000.f)), _frictionCoefficient(100.f), _gravity(800.f)
{
}

void Engine::Rigidbody2D::Update(const float& deltaTime)
{
	// ���� ũ��
	XMVECTOR xmForce = XMVector2Length(XMLoadFloat2(&_force));

	if (0.f != xmForce.m128_f32[0])
	{
		// ���� ����
		XMVECTOR xmDirection = XMVector2Normalize(XMLoadFloat2(&_force));

		// ���ӵ��� ũ��
		float accel = xmForce.m128_f32[0] / _mass;

		// ���ӵ�
		XMStoreFloat2(&_accel, xmDirection * accel);
	}

	// �߰� ���ӵ�
	XMStoreFloat2(&_accel, XMLoadFloat2(&_accel) + XMLoadFloat2(&_addAccel));

	// �ӵ�
	XMStoreFloat2(&_velocity, XMLoadFloat2(&_velocity) + XMLoadFloat2(&_accel) * deltaTime);

	// �����¿����� �ݴ���������� ���ӵ�
	if (0.f != _velocity.x || 0.f != _velocity.y)
	{
		XMVECTOR xmVelocity = XMLoadFloat2(&_velocity);
		XMVECTOR xmFriction = -XMVector2Normalize(xmVelocity) * _frictionCoefficient * deltaTime;

		if (XMVector2Length(xmVelocity).m128_f32[0] < XMVector2Length(xmFriction).m128_f32[0])
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			_velocity = { 0.f, 0.f };
		}
		else
		{
			XMStoreFloat2(&_velocity, xmVelocity + xmFriction);
		}
	}

	// �ִ� �ӵ� ����
	if (fabs(_maxVelocity.x) < fabs(_velocity.x))
	{
		_velocity.x = (_velocity.x / fabs(_velocity.x)) * fabs(_maxVelocity.x);
	}

	if (fabs(_maxVelocity.y) < fabs(_velocity.y))
	{
		_velocity.y = (_velocity.y / fabs(_velocity.y)) * fabs(_maxVelocity.y);
	}

	// �̵�
	XMVECTOR xmVelocity = XMLoadFloat2(&_velocity);
	XMVECTOR xmSpeed = XMVector2Length(xmVelocity);

	if (0.f != xmSpeed.m128_f32[0])
	{
		XMVECTOR xmDirection = XMVector2Normalize(xmVelocity);
		_pTransform->AddPosition(Vector3(xmVelocity.m128_f32[0],
			xmVelocity.m128_f32[1],
			xmVelocity.m128_f32[2]) * deltaTime);
	}

	// �� �ʱ�ȭ
	_force = { 0.f, 0.f };

	// �߰� ���ӵ� �ʱ�ȭ
	_accel = { 0.f, 0.f };
	_addAccel = { 0.f, 0.f };

	Gravity(deltaTime);
}

void Engine::Rigidbody2D::Gravity(const float& deltaTime)
{
	if (_isActiveGravity)
	{
		SetAddAccel(XMFLOAT2(0.f, _gravity));
	}
}

void Engine::Rigidbody2D::AddForce(const XMFLOAT2& force)
{
	XMStoreFloat2(&_force, XMVectorAdd(XMLoadFloat2(&_force), XMLoadFloat2(&force)));
}

void Engine::Rigidbody2D::AddVelocity(const XMFLOAT2& velocity)
{
	_velocity.x += velocity.x;
	_velocity.y += velocity.y;
}

bool Engine::Rigidbody2D::IsActiveGravity() const
{
	return _isActiveGravity;
}

XMFLOAT2 Engine::Rigidbody2D::GetVelocity() const
{
	return _velocity;
}

XMFLOAT2 Engine::Rigidbody2D::GetMaxVelocity() const
{
	return _maxVelocity;
}

void Engine::Rigidbody2D::SetTransform(Transform* pTransform)
{
	_pTransform = pTransform;
}

void Engine::Rigidbody2D::SetMass(const float& mass)
{
	_mass = mass;
}

void Engine::Rigidbody2D::SetVelocity(const XMFLOAT2& velocity)
{
	_velocity = velocity;
}

void Engine::Rigidbody2D::SetMaxVelocity(const XMFLOAT2& velocity)
{
	_maxVelocity = velocity;
}

void Engine::Rigidbody2D::SetFrictionCoefficient(const float& coefficient)
{
	_frictionCoefficient = coefficient;
}

void Engine::Rigidbody2D::SetActiveGravity(bool isActive)
{
	_isActiveGravity = isActive;
}

void Engine::Rigidbody2D::SetGravityScale(float scale)
{
	_gravity = scale;
}

void Engine::Rigidbody2D::SetAddAccel(const XMFLOAT2& accel)
{
	_addAccel = accel;
}

void Engine::Rigidbody2D::Free()
{
}