#include "MainHUD.h"

#include "Client_Define.h"
#include "UI.h"
#include "TextRenderer.h"

MainHUD::MainHUD()
	:MonoBehavior("MainUI")
{

}

void MainHUD::Awake()
{

}

void MainHUD::Start()
{
	UI::UIInfo info;
	info.name = "Timer";
	info.textureTag = L"UI_HUD_Timer_Box";
	info.position = { 200.f, 900.f, 0.f };
	info.scale = { 0.3f, 1.0f, 0.f };
	info.pParent = GetTransform();
	Engine::AddObjectInLayer((int)LayerGroup::UI, "Timer", UI::Create(info));
	
	//_UIs.push_back(_timer);
}

void MainHUD::Update(const float& deltaTime)
{
}

void MainHUD::LateUpdate(const float& deltaTime)
{
}