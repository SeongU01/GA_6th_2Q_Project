#pragma once
#include "GameObject.h"

class Tile:public Engine::GameObject
{
private:
	explicit Tile() = default;
	virtual ~Tile() = default;
private:
	void Initialize(const Vector3& _position, const int _tileIndex);
public:
	static Tile* Create(const Vector3& position, const int _tileIndex);

	bool canMove=true;
};

