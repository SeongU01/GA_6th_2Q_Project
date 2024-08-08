#pragma once
#include "GameObject.h"

class GridMovement;

namespace Engine
{
	class RigidBody2D;
}

class TestPlayer : public Engine::GameObject
{
private:
	explicit TestPlayer() = default;
	virtual ~TestPlayer() = default;

private:
	void Initialize(const Vector3& startPos);
public:
	void ChangeCurrentGrid();
public:
	static TestPlayer* Create(const Vector3& startPos);

};

