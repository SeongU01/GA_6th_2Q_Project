#include "GameOverHUD.h"

GameOverHUD::GameOverHUD()
	:UIComponent(L"GameOver")
{
}

void GameOverHUD::Awake()
{
}

void GameOverHUD::Start()
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

void GameOverHUD::Update(const float& deltaTime)
{
}

void GameOverHUD::LateUpdate(const float& deltaTime)
{
}
