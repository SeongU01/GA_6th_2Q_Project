#include "MPHUD.h"
#include "PlayerMP.h"
MPHUD::MPHUD(PlayerMP* _Mp, int index)
	:UIComponent(L"MP")
{

	_hpColor = index;
	_pMP = _Mp;
}

void MPHUD::Awake()
{
}

void MPHUD::Start()
{
	UI::UIInfo info;
	UI* pObj;
	for (int i = 0; i < 5; i++) {
		info = CreateInfo(L"HPBackground", L"UI_HUD_HP", 0, {
			(float)(300+(i * 10)),950.0f , 2.f }, { 1.0f,1.0f,1.f }, &transform);
		_HPBar.push_back(AddUI(info));
	}
}

void MPHUD::Update(const float& deltaTime)
{
	int currentHP = _pMP->GetMP();
	for (int i = 0; i < 5; i++)
	{
		if (i < currentHP)
			_HPBar[i]->SetFrame(_hpColor);
		else
			_HPBar[i]->SetFrame(2);
	}
}

void MPHUD::LateUpdate(const float& deltaTime)
{
} 
