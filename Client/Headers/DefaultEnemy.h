#pragma once
#include "GameObject.h"

class DefaultEnemy :public Engine::GameObject
{
private:
	explicit DefaultEnemy() = default;
	virtual ~DefaultEnemy() = default;

private:
	void Initialize();
public:
	static DefaultEnemy* Create();
};