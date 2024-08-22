#include "TitleButtons.h"
#include "Button.h"
#include "InfoHUD.h"
#include "Stage1Scene.h"
#include "CreditHUD.h"
#include "Client_Define.h"
#include "CutScene.h"
#include "ToolTip.h"

#include "EventManager.h"
#include "CardManager.h"

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
	info = CreateInfo(L"TitleButton", L"Title", 7, { 313.f, 450.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);

	Button* btn = pObj->AddComponent<Button>();
	btn->SetIsReat(false);
	btn->SetCancel([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(7); });
	btn->SetOnHover([pObj]()
		{ 
			Sound::PlaySound("Effect_Sound_Button_Hover", (int)SoundGroup::SFX, 0.8f, false);
			pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(8);
		});
	btn->SetOnPressed([]()
		{
			std::wstring filePath = rootPath;			

			// 카드 데이터
			CardManager::ResetInstance();
			CardManager* pCardManager = CardManager::GetInstance();
			pCardManager->LoadCard((filePath + L"Data/Card").c_str());
			pCardManager->SetDontDestroyObject(true);
			pCardManager->SetRenderGroup((int)RenderGroup::None);

			Engine::AddObjectInLayer((int)LayerGroup::UI, L"Manager", pCardManager);

			EventManager::ResetInstance();
			EventManager* pEventManager = EventManager::GetInstance();
			pEventManager->SetDontDestroyObject(true);
			pEventManager->SetRenderGroup((int)RenderGroup::None);
			pEventManager->Initialize();
			Engine::AddObjectInLayer((int)LayerGroup::UI, L"Manager", pEventManager);

			Sound::PlaySound("Effect_Sound_Button_Click", (int)SoundGroup::SFX, 0.8f, false);
			Engine::ChangeScene(CutScene::Create(1));
		});
	btn->SetRange(info.position, pObj->GetImageSize());

	//상세설명버튼
	info = CreateInfo(L"TitleButton", L"Title", 3, { 400.f, 570.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);

	btn = pObj->AddComponent<Button>();
	btn->SetIsReat(false);
	btn->SetCancel([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(3); });
	btn->SetOnHover([pObj]() { 
		Sound::PlaySound("Effect_Sound_Button_Hover", (int)SoundGroup::SFX, 0.8f, false);
		pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(4); 
		});
	btn->SetOnPressed([]() {
		Sound::PlaySound("Effect_Sound_Button_Click", (int)SoundGroup::SFX, 0.8f, false);
		Sound::PlaySound("Effect_Sound_FX_UI_Popup", (int)SoundGroup::SFX, 0.8f, false);
		CreditHUD* pCredit = Engine::FindObject((int)LayerGroup::UI, L"Credit", NULL)->GetComponent<CreditHUD>();
		pCredit->SetActives(false);
		InfoHUD* pInfo =  Engine::FindObject((int)LayerGroup::UI, L"Info", NULL)->GetComponent<InfoHUD>();
		pInfo->SetActives(true);
		});
	btn->SetRange(info.position, pObj->GetImageSize());

	//크래딧버튼
	info = CreateInfo(L"TitleButton", L"Title", 5, { 355.f, 690.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);

	btn = pObj->AddComponent<Button>();
	btn->SetIsReat(false);
	btn->SetCancel([pObj]() { pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(5); });
	btn->SetOnHover([pObj]() {
		Sound::PlaySound("Effect_Sound_Button_Hover", (int)SoundGroup::SFX, 0.8f, false);
		pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(6); });
	btn->SetOnPressed([]() {
		Sound::PlaySound("Effect_Sound_Button_Click", (int)SoundGroup::SFX, 0.8f, false);
		Sound::PlaySound("Effect_Sound_FX_UI_Popup", (int)SoundGroup::SFX, 0.8f, false);
		InfoHUD* pInfo = Engine::FindObject((int)LayerGroup::UI, L"Info", NULL)->GetComponent<InfoHUD>();
		pInfo->SetActives(false);
		  CreditHUD* pCredit = Engine::FindObject((int)LayerGroup::UI, L"Credit", NULL)->GetComponent<CreditHUD>();
		  pCredit->SetActives(true);
		});
	btn->SetRange(info.position, pObj->GetImageSize());

	//나가기버튼
	info = CreateInfo(L"TitleButton", L"Title", 1, { 305.f, 810.f, -1.f }, { 1.f, 1.f, 1.f }, &transform);
	pObj = AddUI(info);
	btn = pObj->AddComponent<Button>();
	btn->SetIsReat(false);
	btn->SetCancel([pObj]() { 
		pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(1); });
	btn->SetOnHover([pObj]() {
		Sound::PlaySound("Effect_Sound_Button_Hover", (int)SoundGroup::SFX, 0.8f, false);
		pObj->GetComponent<Engine::SpriteRenderer>()->SetIndex(2); 
		});
	btn->SetOnPressed([]() {
		Sound::PlaySound("Effect_Sound_Button_Click", (int)SoundGroup::SFX, 0.8f, false);
		PostQuitMessage(0);
		});
	btn->SetRange(info.position, pObj->GetImageSize());

	//SetDontDestroyObject(true);
}

void TitleButtons::Update(const float& deltaTime)
{
}

void TitleButtons::LateUpdate(const float& deltaTime)
{
}
