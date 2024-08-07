#pragma once
#include "GameObject.h"
class Obstacle:public Engine::GameObject
{
private:
	explicit Obstacle() = default;
	virtual ~Obstacle() = default;
private:
	void initialize(const std::pair<Vector3, Vector3>& gridRange, const wchar_t* textureTag=nullptr);
public:
	static Obstacle* Create(const std::pair<Vector3, Vector3>& gridRange, const wchar_t* textureTag = nullptr);
};

