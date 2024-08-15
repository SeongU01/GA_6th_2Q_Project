#include "HPHUD.h"
#include "HP.h"
#include "Client_Define.h"

HPHUD::HPHUD(HP* _hp,int index)
	:UIComponent(L"HP")
{
	_hpColor = index;
	_pHP = _hp;
}

void HPHUD::Awake()
{
}

void HPHUD::Start()
{
	UI::UIInfo info;
	UI* pObj;
	for (int i = 0; i < _pHP->GetMaxHP(); i++) {
		info = CreateInfo(L"HPBackground", L"UI_HUD_HP", 0, {
			(float)((i * 10) - (_pHP->GetMaxHP() / 2 * 10)),40.0f , -1000.f}, {1.0f,1.0f,1.f}, &transform);
		pObj = AddUI(info);
		// pObj->SetRenderGroup((int)RenderGroup::Object);
		_HPBar.push_back(pObj);
	}
	SetDontDestroyObject(true);
}

void HPHUD::Update(const float& deltaTime)
{
	int currentHP = _pHP->GetHP();
	int maxHP = _pHP->GetMaxHP();
	
	for (auto& ui : _UIs)
	{
		if (0.f > transform.scale.x)
			ui->SetScale({ -1.f, 1.f, 0.f });
		else
			ui->SetScale({ 1.f, 1.f, 0.f });
	}

	for (int i = 0; i < maxHP; i++)
	{
		if (i < currentHP)
			_HPBar[i]->SetFrame(_hpColor);
		else
			_HPBar[i]->SetFrame(2);
	}
}

void HPHUD::LateUpdate(const float& deltaTime)
{
}
