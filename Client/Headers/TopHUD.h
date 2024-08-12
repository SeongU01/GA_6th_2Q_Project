#pragma once
#include "UIComponent.h"
class HP;
class TopHUD : public UIComponent
{
public:
	explicit TopHUD(HP* _hp, int index);
	explicit TopHUD();
	//explicit HPHUD(HP* _hp) { _pHP = _hp; };
private:
	virtual ~TopHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	HP* _pHP = nullptr;
	int _hpColor; //0: 플레이어초록 , 1: 적빨강
	std::vector<UI*> _HPBar;
};
