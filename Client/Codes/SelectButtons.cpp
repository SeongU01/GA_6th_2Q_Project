#include "SelectButtons.h"
#include "Button.h"

#include "Client_Define.h"

#include "CutScene.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Stage3Scene.h"
#include "Stage4Scene.h"
SelectButtons::SelectButtons()
	:UIComponent(L"SelectButtons")
{
}

void SelectButtons::Awake()
{
}

void SelectButtons::Start()
{
	UI::UIInfo info;
	UI* pObj;
	//스테이지 1
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 400.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	Button* btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	//btn->SetOnPressed([]() {Scene::ChagneScene(CutScene::Create(1)); });
	btn->SetOnPressed([]() {Scene::ChagneScene(Stage1Scene::Create()); });
	btn->SetRange(info.position, pObj->GetImageSize());
	//스테이지 2
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 700.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {Scene::ChagneScene(Stage2Scene::Create()); });
	btn->SetRange(info.position, pObj->GetImageSize());
	//스테이지 3
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 1000.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {Scene::ChagneScene(Stage3Scene::Create()); });
	btn->SetRange(info.position, pObj->GetImageSize());
	//스테이지 4
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 1300.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {Scene::ChagneScene(Stage4Scene::Create()); });
	btn->SetRange(info.position, pObj->GetImageSize());

	//SetDontDestroyObject(true);
}

void SelectButtons::Update(const float& deltaTime)
{
}

void SelectButtons::LateUpdate(const float& deltaTime)
{
}
