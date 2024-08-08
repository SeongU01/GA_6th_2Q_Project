#pragma once
#include "UIComponent.h"

class HPHUD : public UIComponent
{
public:
	explicit HPHUD();
private:
	virtual ~HPHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
};
