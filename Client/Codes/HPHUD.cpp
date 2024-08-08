#include "HPHUD.h"

HPHUD::HPHUD()
	:UIComponent(L"HP")
{
}

void HPHUD::Awake()
{
}

void HPHUD::Start()
{
	UI::UIInfo info;
	UI* pObj;
	//À½.
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, {100.f,100.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	SetDontDestroyObject(true);
}

void HPHUD::Update(const float& deltaTime)
{
}

void HPHUD::LateUpdate(const float& deltaTime)
{
}
