#include "Rigidbody2D.h"
#include "Transform.h"

using namespace Engine;

Engine::Rigidbody2D::Rigidbody2D(const char* name)
	: Component(name), _maxVelocity(Vector3(1000.f, 1000.f, 0.f)), _frictionCoefficient(100.f), _gravity(800.f)
{	
}

void Engine::Rigidbody2D::Initialize()
{
	_pTransform = _pOwner->GetTransform();
}

void Engine::Rigidbody2D::Update(const float& deltaTime)
{
	// ���� ũ��
	XMVECTOR xmForce = XMVector3Length(_force);

	if (0.f != xmForce.m128_f32[0])
	{
		// ���� ����
		XMVECTOR xmDirection = XMVector3Normalize(_force);

		// ���ӵ��� ũ��
		float accel = xmForce.m128_f32[0] / _mass;

		// ���ӵ�
		_accel = xmDirection * accel;
	}

	// �߰� ���ӵ�
	_accel += _addAccel;

	// �ӵ�
	_velocity += _accel * deltaTime;

	// �����¿����� �ݴ���������� ���ӵ�
	if (0.f != _velocity.x || 0.f != _velocity.y)
	{
		XMVECTOR xmVelocity = _velocity;
		XMVECTOR xmFriction = -XMVector3Normalize(xmVelocity) * _frictionCoefficient * deltaTime;

		if (XMVector3Length(xmVelocity).m128_f32[0] < XMVector3Length(xmFriction).m128_f32[0])
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			_velocity = { 0.f, 0.f, 0.f };
		}
		else
		{
			_velocity = xmVelocity + xmFriction;
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
	XMVECTOR xmVelocity = _velocity;
	XMVECTOR xmSpeed = XMVector3Length(xmVelocity);

	if (0.f != xmSpeed.m128_f32[0])
	{
		XMVECTOR xmDirection = XMVector3Normalize(xmVelocity);
		_pTransform->position += xmVelocity * deltaTime;
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
		SetAddAccel(Vector3(0.f, _gravity, 0.f));
	}
}

void Engine::Rigidbody2D::AddForce(const Vector3& force)
{
	_force += force;
}

void Engine::Rigidbody2D::AddVelocity(const Vector3& velocity)
{
	_velocity.x += velocity.x;
	_velocity.y += velocity.y;
}

void Engine::Rigidbody2D::Free()
{
}