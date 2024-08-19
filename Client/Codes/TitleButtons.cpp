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
	info = CreateInfo(L"TitleButton", L"Title", 7, { 400.f, 450.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);

	Button* btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(7); });
	btn->SetOnHover([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(8); });
	btn->SetOnPressed([]() { Scene::ChagneScene(SelectScene::Create()); });
	btn->SetRange(info.position, pObj->GetImageSize());

	//상세설명버튼
	info = CreateInfo(L"TitleButton", L"Title", 3, { 400.f, 550.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);

	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(3); });
	btn->SetOnHover([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(4); });
	btn->SetOnPressed([]() {
		Sound::StopSound((int)SoundGroup::SFX);
		Sound::PlaySound("Effect_Sound_FX_UI_Popup", (int)SoundGroup::SFX, 0.8f, false);
		InfoHUD* pInfo =  Engine::FindObject((int)LayerGroup::UI, L"Info", NULL)->GetComponent<InfoHUD>();
		pInfo->SetActives(true);
		});
	btn->SetRange(info.position, pObj->GetImageSize());

	//크래딧버튼
	info = CreateInfo(L"TitleButton", L"Title", 5, { 400.f, 650.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);

	btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(5); });
	btn->SetOnHover([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(6); });
	btn->SetOnPressed([]() {
		Sound::StopSound((int)SoundGroup::SFX);
		Sound::PlaySound("Effect_Sound_FX_UI_Popup", (int)SoundGroup::SFX, 0.8f, false);
		  CreditHUD* pCredit = Engine::FindObject((int)LayerGroup::UI, L"Credit", NULL)->GetComponent<CreditHUD>();
		  pCredit->SetActives(true);
		});
	btn->SetRange(info.position, pObj->GetImageSize());

	//나가기버튼
	info = CreateInfo(L"TitleButton", L"Title", 1, { 400.f, 750.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();

	btn->SetCancel([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(1); });
	btn->SetOnHover([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(2); });
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
