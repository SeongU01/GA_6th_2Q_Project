#pragma once
#include "GameObject.h"

class TimerUI : public Engine::GameObject
{
private:
	explicit TimerUI() = default;
	virtual ~TimerUI() = default;
private:
	void Initialize();
public:
	static TimerUI* Create();
};