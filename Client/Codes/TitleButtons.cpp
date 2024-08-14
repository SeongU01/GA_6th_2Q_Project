#include "TitleButtons.h"
#include "Button.h"
#include "InfoHUD.h"
#include "CreditHUD.h"
#include "Client_Define.h"

#include "SelectScene.h"
#include "ToolTip.h"
TitleButtons::TitleButtons()
	:UIComponent(L"TitleButtons")
{
}

void TitleButtons::Awake()
{
}

void TitleButtons::Start()
{
	UI::UIInfo info;
	UI* pObj;
	//시작버튼
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button",0, { 1800.f,400.f, - 1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	Button* btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {Scene::ChagneScene(SelectScene::Create()); });
	btn->SetRange(info.position, pObj->GetImageSize());
	//상세설명버튼
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 1800.f,500.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);

	btn = pObj->AddComponent<Button>();
	btn->SetOnPressed([]() {
		InfoHUD* pInfo =  Engine::FindObject((int)LayerGroup::UI, L"Info", NULL)->GetComponent<InfoHUD>();
		pInfo->SetActives(true);
		});
	btn->SetRange(info.position, pObj->GetImageSize());
	//크래딧버튼
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 1800.f,600.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() {
		  CreditHUD* pCredit = Engine::FindObject((int)LayerGroup::UI, L"Credit", NULL)->GetComponent<CreditHUD>();
		  pCredit->SetActives(true);
		});
	btn->SetRange(info.position, pObj->GetImageSize());
	//나가기버튼
	info = CreateInfo(L"TitleButton", L"UI_HUD_Button", 0, { 1800.f,700.f, -1.f }, { 1.f,1.f,1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale({ 1.0f,1.0f,1.0f }); });
	btn->SetOnHover([pObj]() { pObj->AddScale({ 0.0001f,0.0001f,0.0f }); });
	btn->SetOnPressed([]() { PostQuitMessage(0);});
	btn->SetRange(info.position, pObj->GetImageSize());
	//SetDontDestroyObject(true);
}

void TitleButtons::Update(const float& deltaTime)
{
}

void TitleButtons::LateUpdate(const float& deltaTime)
{
}
