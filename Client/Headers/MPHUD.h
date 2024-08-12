#pragma once
#include "UIComponent.h"

class PlayerMP;
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
	PlayerMP* _pMP = nullptr;
	int _hpColor; //0: �÷��̾��ʷ� , 1: ������
	std::vector<UI*> _HPBar;
};
