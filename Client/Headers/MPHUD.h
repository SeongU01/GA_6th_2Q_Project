#pragma once
#include "UIComponent.h"

class PlayerMP;
class ToolTip;
class MPHUD : public UIComponent
{
public:
	explicit MPHUD(PlayerMP* _Mp, int index);
	explicit MPHUD();
	//explicit HPHUD(HP* _hp) { _pHP = _hp; };
private:
	virtual ~MPHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	ToolTip* _ptoolTip = nullptr;
	PlayerMP* _pMP = nullptr;
	int _mpColor; //0: 플레이어초록 , 1: 적빨강
	std::vector<UI*> _MPBar;
};
