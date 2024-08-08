#pragma once
#include "UIComponent.h"

class CreditHUD : public UIComponent
{
public:
	explicit CreditHUD();
private:
	virtual ~CreditHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

