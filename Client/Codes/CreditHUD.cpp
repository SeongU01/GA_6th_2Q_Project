#include "CreditHUD.h"

#include "Client_Define.h"
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
	info = CreateInfo(L"HPBackground", L"UI_HUD_Popup", 0, Vector3(WINCX >> 1, WINCY >> 1, 0.f), { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	SetActives(false);
}

void CreditHUD::Update(const float& deltaTime)
{
}

void CreditHUD::LateUpdate(const float& deltaTime)
{
}
