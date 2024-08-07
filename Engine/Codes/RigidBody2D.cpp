#include "Rigidbody2D.h"
#include "Transform.h"

using namespace Engine;

Engine::Rigidbody2D::Rigidbody2D(const wchar_t* name)
	: Component(name), _maxVelocity(Vector3(1000.f, 1000.f, 0.f)), _frictionCoefficient(100.f), _gravity(800.f)
{	
}

void Engine::Rigidbody2D::Update(const float& deltaTime)
{
	// 힘의 크기
	XMVECTOR xmForce = XMVector3Length(_force);

	if (0.f != xmForce.m128_f32[0])
	{
		// 힘의 방향
		XMVECTOR xmDirection = XMVector3Normalize(_force);

		// 가속도의 크기
		float accel = xmForce.m128_f32[0] / _mass;

		// 가속도
		_accel = xmDirection * accel;
	}

	// 추가 가속도
	_accel += _addAccel;

	// 속도
	_velocity += _accel * deltaTime;

	// 마찰력에의한 반대방향으로의 가속도
	if (0.f != _velocity.x || 0.f != _velocity.y)
	{
		XMVECTOR xmVelocity = _velocity;
		XMVECTOR xmFriction = -XMVector3Normalize(xmVelocity) * _frictionCoefficient * deltaTime;

		if (XMVector3Length(xmVelocity).m128_f32[0] < XMVector3Length(xmFriction).m128_f32[0])
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			_velocity = { 0.f, 0.f, 0.f };
		}
		else
		{
			_velocity = xmVelocity + xmFriction;
		}
	}

	// 최대 속도 제한
	if (fabs(_maxVelocity.x) < fabs(_velocity.x))
	{
		_velocity.x = (_velocity.x / fabs(_velocity.x)) * fabs(_maxVelocity.x);
	}

	if (fabs(_maxVelocity.y) < fabs(_velocity.y))
	{
		_velocity.y = (_velocity.y / fabs(_velocity.y)) * fabs(_maxVelocity.y);
	}

	// 이동
	XMVECTOR xmVelocity = _velocity;
	XMVECTOR xmSpeed = XMVector3Length(xmVelocity);

	if (0.f != xmSpeed.m128_f32[0])
	{
		XMVECTOR xmDirection = XMVector3Normalize(xmVelocity);
		transform->position += Vector3(xmVelocity * deltaTime);
	}

	// 힘 초기화
	_force = { 0.f, 0.f };

	// 추가 가속도 초기화
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