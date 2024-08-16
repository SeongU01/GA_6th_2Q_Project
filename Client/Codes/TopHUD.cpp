#include "TopHUD.h"
#include "HP.h"
#include "Client_Define.h"
TopHUD::TopHUD(HP* _hp, int index)
	:UIComponent(L"HP")
{
	_hpColor = index;
	_pHP = _hp;
}

void TopHUD::Awake()
{
}

void TopHUD::Start()
{
	UI::UIInfo info;
	info = CreateInfo(L"HPBackground", L"UI_HUD_HP_Top", 0, 
		{80.0f ,40.0f , -1.f }, { 1.2f,1.2f,1.f }, &transform);
	 AddUI(info)->SetRenderGroup((int)RenderGroup::UI);
	for (int i = 0; i < _pHP->GetMaxHP(); i++) {
		info = CreateInfo(L"HPstate", L"UI_HUD_HP_Top", 2, {
			33+(float)(i * 23) ,40.0f , 100.f }, { 1.0f,1.0f,1.f }, &transform);
		_HPBar.push_back(AddUI(info));
		_HPBar.back()->SetRenderGroup((int)RenderGroup::UI);
	}
	SetDontDestroyObjectUI(true);
}

void TopHUD::Update(const float& deltaTime)
{
	int currentHP = _pHP->GetHP();
	for (int i = 0; i < _pHP->GetMaxHP(); i++)
	{
		if (i < currentHP)
			_HPBar[i]->SetFrame(_hpColor);
		else
			_HPBar[i]->SetFrame(1);
	}
}

void TopHUD::LateUpdate(const float& deltaTime)
{
}
