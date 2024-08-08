#pragma once
#include "UIComponent.h"

class InfoHUD : public UIComponent
{
public:
	explicit InfoHUD();
private:
	virtual ~InfoHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

