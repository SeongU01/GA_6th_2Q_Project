#include "GameClearButtons.h"
#include "Button.h"

#include "Client_Define.h"

#include "SelectScene.h"
GameClearButtons::GameClearButtons()
	:UIComponent(L"SelectButtons")
{
}

void GameClearButtons::Awake()
{
}

void GameClearButtons::Start()
{
	UI::UIInfo info;
	UI* pObj;
	//카드1
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 400.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	Button* btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {
		Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->SetActive(false);
		Scene::ChagneScene(SelectScene::Create());
		});
	btn->SetRange(info.position, pObj->GetImageSize());
	//카드2
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 700.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {
		Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->SetActive(false);
		Scene::ChagneScene(SelectScene::Create());
		});
	btn->SetRange(info.position, pObj->GetImageSize());
	//카드3
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 1000.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {
		Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->SetActive(false);
		Scene::ChagneScene(SelectScene::Create());
		});
	btn->SetRange(info.position, pObj->GetImageSize());
	SetActives(false);
}

void GameClearButtons::Update(const float& deltaTime)
{
}

void GameClearButtons::LateUpdate(const float& deltaTime)
{
}
