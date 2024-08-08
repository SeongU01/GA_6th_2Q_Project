#pragma once
#include "GameObject.h"

class DeckUI : public Engine::GameObject
{
private:
	explicit DeckUI() = default;
	virtual ~DeckUI() = default;

private:
	bool Initialize();

public:
	static DeckUI* Create();
};

