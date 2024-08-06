#pragma once
#include "GameObject.h"
#include "UI.h"

class TimerUI : public Engine::GameObject
{
private:
	explicit TimerUI() = default;
	virtual ~TimerUI() = default;
private:
	void Initialize();
public:
	static TimerUI* Create();
private:
	std::vector<UI*> _UIs;
	UI::UIInfo ui;
};