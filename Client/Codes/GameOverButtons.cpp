#include "GameOVerButtons.h"
#include "Button.h"

#include "Client_Define.h"

#include "TitleScene.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Stage3Scene.h"
#include "Stage4Scene.h"
GameOVerButtons::GameOVerButtons()
	:UIComponent(L"SelectButtons")
{
}

void GameOVerButtons::Awake()
{
}

void GameOVerButtons::Start()
{
	UI::UIInfo info;
	UI* pObj;
	//다시하기(해당스테이지 재시도)
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 400.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	Button* btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {Scene::ChagneScene(Stage1Scene::Create()); });
	btn->SetRange(info.position, pObj->GetImageSize());
	//타이틀로
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 700.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {
		Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->SetActive(false);
		Scene::ChagneScene(TitleScene::Create()); 
		});
	btn->SetRange(info.position, pObj->GetImageSize());
	SetActives(false);
}

void GameOVerButtons::Update(const float& deltaTime)
{
}

void GameOVerButtons::LateUpdate(const float& deltaTime)
{
}
