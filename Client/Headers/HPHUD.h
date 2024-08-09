#pragma once
#include "UIComponent.h"

class HP;
class HPHUD : public UIComponent
{
public:
	explicit HPHUD();//�ӽ�.
	//explicit HPHUD(HP* _hp) { _pHP = _hp; };
private:
	virtual ~HPHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	HP* _pHP = nullptr;
};
