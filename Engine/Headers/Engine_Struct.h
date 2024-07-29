#pragma once

struct Vector3
{
	Vector3() = default;
	Vector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) {}

	Vector3& operator+=(const Vector3& vector)
	{
		this->x += vector.x;
		this->y += vector.y;
		this->z += vector.z;

		return *this;
	}

	Vector3& operator+=(const float& value)
	{
		this->x += value;
		this->y += value;
		this->z += value;

		return *this;
	}

	Vector3 operator+(const Vector3& vector) const
	{
		Vector3 temp;

		temp.x = this->x + vector.x;
		temp.y = this->y + vector.y;
		temp.z = this->z + vector.z;

		return temp;
	}

	Vector3 operator+(const float& value) const
	{
		Vector3 temp;

		temp.x = this->x + value;
		temp.y = this->y + value;
		temp.z = this->z + value;

		return temp;
	}

	Vector3& operator-=(const Vector3& vector)
	{
		this->x -= vector.x;
		this->y -= vector.y;
		this->z -= vector.z;

		return *this;
	}

	Vector3& operator-=(const float& value)
	{
		this->x -= value;
		this->y -= value;
		this->z -= value;

		return *this;
	}

	Vector3 operator-(const Vector3& vector) const
	{
		Vector3 temp;

		temp.x = this->x - vector.x;
		temp.y = this->y - vector.y;
		temp.z = this->z - vector.z;

		return temp;
	}

	Vector3 operator-(const float& value) const
	{
		Vector3 temp;

		temp.x = this->x - value;
		temp.y = this->y - value;
		temp.z = this->z - value;

		return temp;
	}

	Vector3& operator-()
	{
		return *this *= -1.f;;
	}

	Vector3 operator*(const float& value) const
	{
		Vector3 temp;
		temp.x = this->x * value;
		temp.y = this->y * value;
		temp.z = this->z * value;

		return temp;
	}

	Vector3& operator*=(const Vector3& vector)
	{
		this->x *= vector.x;
		this->y *= vector.y;
		this->z *= vector.z;

		return *this;
	}

	Vector3& operator*=(const float& value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;

		return *this;
	}

	void Abs()
	{
		x = fabs(x); y = fabs(y); z = fabs(z);
	}
	float Length() const
	{
		return sqrtf((this->x * this->x + this->y * this->y));
	}
	float SqrMagnitude() const
	{
		return this->x * this->x + this->y * this->y;
	}
	Vector3 Normalized()
	{
		float length = Length();
		this->x /= length;
		this->y /= length;

		return *this;
	}
	void RotationZ(const float& radian)
	{
		Vector3 temp = *this;
		this->x = temp.x * cosf(radian) - temp.y * sinf(radian);
		this->y = temp.x * sinf(radian) + temp.y * cosf(radian);
	}

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};

namespace Engine
{
	class Collider;
}
struct CollisionInfo
{
	Engine::Collider* other = nullptr;
	Engine::Collider* itSelf = nullptr;
};