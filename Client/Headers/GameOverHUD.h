#pragma once
#include "UIComponent.h"

class GameOverHUD : public UIComponent
{
public:
	explicit GameOverHUD();
private:
	virtual ~GameOverHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

