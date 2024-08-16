#pragma once
#include "UIComponent.h"

class HP;
class HPHUD : public UIComponent
{
public:
	explicit HPHUD(HP* _hp,int index);

private:
	virtual ~HPHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	void Free() override;

private:
	std::vector<UI*> _HPBar;
	HP* _pHP = nullptr;
	int _hpColor; //0: 플레이어초록 , 1: 적빨강
};
