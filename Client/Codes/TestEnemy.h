#pragma once
#include "GameObject.h"

class GridMovement;

namespace Engine
{
	class RigidBody2D;
}

class TestEnemy : public Engine::GameObject
{
private:
	explicit TestEnemy() = default;
	virtual ~TestEnemy() = default;

private:
	void Initialize();

public:
	static TestEnemy* Create();

};

