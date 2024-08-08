#pragma once
#include "UIComponent.h"
class TitleButtons:public UIComponent
{
public:
	explicit TitleButtons();
private:
	virtual ~TitleButtons() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

