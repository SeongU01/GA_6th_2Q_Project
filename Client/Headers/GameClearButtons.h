#pragma once
#include "UIComponent.h"

class GameClearButtons :public UIComponent
{
public:
	explicit GameClearButtons();
private:
	virtual ~GameClearButtons() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

