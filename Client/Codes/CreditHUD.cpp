#include "CreditHUD.h"

CreditHUD::CreditHUD()
	:UIComponent(L"Credit")
{
}

void CreditHUD::Awake()
{
}

void CreditHUD::Start()
{
	UI::UIInfo info;
	UI* pObj;
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 100.f,100.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 200.f,100.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 300.f,100.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	SetActives(false);
}

void CreditHUD::Update(const float& deltaTime)
{
}

void CreditHUD::LateUpdate(const float& deltaTime)
{
}
