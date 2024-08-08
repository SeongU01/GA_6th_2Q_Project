#include "InfoHUD.h"

InfoHUD::InfoHUD()
	:UIComponent(L"Info")
{
}

void InfoHUD::Awake()
{
}

void InfoHUD::Start()
{
	UI::UIInfo info;
	UI* pObj;
	//À½.
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 100.f,400.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 200.f,400.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 300.f,400.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	SetActives(false);
}

void InfoHUD::Update(const float& deltaTime)
{
}

void InfoHUD::LateUpdate(const float& deltaTime)
{
}
