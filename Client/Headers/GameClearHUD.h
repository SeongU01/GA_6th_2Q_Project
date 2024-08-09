#pragma once
#include "UIComponent.h"

class GameClearHUD : public UIComponent
{
public:
	explicit GameClearHUD();
private:
	virtual ~GameClearHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

