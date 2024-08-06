#include "MainHUD.h"

#include "Client_Define.h"
#include "UI.h"
#include "TimerUI.h"
#include "Button.h"


MainHUD::MainHUD()
	:MonoBehavior(L"MainUI")
{

}

void MainHUD::Awake()
{

}

void MainHUD::Start()
{
	Engine::AddObjectInLayer(
		(int)LayerGroup::UI, L"TimerText",
		TimerUI::Create()
	);

	UI::UIInfo info;
	info.name = L"name";
	info.textureTag = L"UI_HUD_Timer_Box";
	info.fixFrame = 0;
	info.position = { 100.0f , 600.f, -1.f };
	info.scale = { 0.4f, 1.0f, 1.0f };
	info.pParent = GetTransform();
	UI* pObj = UI::Create(info);
	Engine::AddObjectInLayer(
		(int)LayerGroup::UI, L"Buttons",
		pObj
	);
	Button* btn = pObj->AddComponent<Button>();
	btn->SetCancel([pObj]() { pObj->SetScale( { 1.0,1.0,1.0 }); });
	btn->SetOnHover([pObj]() { pObj->AddScale( { 0.0001,0.0001,0.0 }); });
	btn->SetOnPressed([pObj]() { pObj->SetActive(false); });

}

void MainHUD::Update(const float& deltaTime)
{
}

void MainHUD::LateUpdate(const float& deltaTime)
{
}
//플레이어를 따라오는 적.. enemy