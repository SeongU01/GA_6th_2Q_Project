#pragma once
#include "UIComponent.h"
class SelectButtons :public UIComponent
{
public:
	explicit SelectButtons();
private:
	virtual ~SelectButtons() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};

