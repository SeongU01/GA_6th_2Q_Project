#pragma once
#include "GameObject.h"

class Canvas : public Engine::GameObject
{
private:
	explicit Canvas() = default;
	virtual ~Canvas() = default;
private:
	void Initialize(const char* name);

public:
	static Canvas* Create(const char* name);
};