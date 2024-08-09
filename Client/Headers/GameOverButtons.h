#pragma once
#include "UIComponent.h"
class GameOVerButtons :public UIComponent
{
public:
	explicit GameOVerButtons();
private:
	virtual ~GameOVerButtons() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

