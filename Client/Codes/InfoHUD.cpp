#include "InfoHUD.h"

#include "Client_Define.h"
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
	info = CreateInfo(L"HPBackground", L"UI_HUD_Popup", 0, Vector3(WINCX >> 1, WINCY >> 1, 0.f), { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	SetActives(false);
}

void InfoHUD::Update(const float& deltaTime)
{
}

void InfoHUD::LateUpdate(const float& deltaTime)
{
}
