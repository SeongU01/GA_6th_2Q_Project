#pragma once
#include "GameObject.h"

class Tile:public Engine::GameObject
{
private:
	explicit Tile() = default;
	virtual ~Tile() = default;
private:
	void Initialize(const Vector3& _position);
public:
	static Tile* Create(const Vector3& position);
};

