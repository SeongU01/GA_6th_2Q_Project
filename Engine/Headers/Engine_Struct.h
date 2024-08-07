#pragma once

struct Vector3 : public XMFLOAT3
{
	Vector3() = default;
	Vector3(float _x, float _y, float _z)
	{ x = _x; y = _y; z = _z; }
	Vector3(const XMVECTOR& other) { XMStoreFloat3(this, other); }

	void operator=(const XMVECTOR& other) { XMStoreFloat3(this, other); }
	operator XMFLOAT3() { return *this; }
	operator XMVECTOR() { return XMLoadFloat3(this); }

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
		Vector3 temp{};

		temp.x = this->x + vector.x;
		temp.y = this->y + vector.y;
		temp.z = this->z + vector.z;

		return temp;
	}

	Vector3 operator+(const float& value) const
	{
		Vector3 temp{};

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
		Vector3 temp{};

		temp.x = this->x - vector.x;
		temp.y = this->y - vector.y;
		temp.z = this->z - vector.z;

		return temp;
	}

	Vector3 operator-(const float& value) const
	{
		Vector3 temp{};

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
		Vector3 temp{};

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
	bool operator==(const Vector3& other) const {
		return ((int)x == (int)other.x && (int)y == (int)other.y && (int)z == (int)other.z);
	}
};