#include "GameClearHUD.h"

GameClearHUD::GameClearHUD()
	:UIComponent(L"GameClear")
{
}

void GameClearHUD::Awake()
{
}

void GameClearHUD::Start()
{
	UI::UIInfo info;
	UI* pObj;
	//À½.
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 100.f,100.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 200.f,100.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	info = CreateInfo(L"HPBackground", L"UI_HUD_Button", 0, { 300.f,100.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	SetActives(false);
}

void GameClearHUD::Update(const float& deltaTime)
{
}

void GameClearHUD::LateUpdate(const float& deltaTime)
{
}
