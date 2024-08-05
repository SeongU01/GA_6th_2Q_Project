#pragma once
#include "GameObject.h"

class Card final : public Engine::GameObject
{
private:
	explicit Card() = default;
	virtual ~Card() = default;

private:
	void Initialize();
public:
	static Card* Create();
};

