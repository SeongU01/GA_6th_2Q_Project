#pragma once
#include "GameObject.h"

class Map :public Engine::GameObject
{
private:
	explicit Map() = default;
	virtual ~Map() = default;
private:
	void Initialize(const Vector3& matrix, const Vector3& offset, const Vector3& position);
public:
	static Map* Create(const Vector3& matrix, const Vector3& offset, const Vector3& position);
};

