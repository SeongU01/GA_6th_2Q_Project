#pragma once
#include "GameObject.h"
#include "TimerSystem.h"

class Canvas : public Engine::GameObject
{
private:
	explicit Canvas() = default;
	virtual ~Canvas() = default;
private:
	void Initialize(const wchar_t* name);

public:
	static Canvas* Create(const wchar_t* name);
};