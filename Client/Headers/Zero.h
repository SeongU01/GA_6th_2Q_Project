#pragma once
#include "GameObject.h"

class GridMovement;

namespace Engine
{
	class RigidBody2D;
}

class Zero : public Engine::GameObject
{
private:
	explicit Zero() = default;
	virtual ~Zero() = default;

private:
	void Initialize(const Vector3& startPos);
public:
	void ChangeCurrentGrid();
public:
	static Zero* Create(const Vector3& startPos);

};

