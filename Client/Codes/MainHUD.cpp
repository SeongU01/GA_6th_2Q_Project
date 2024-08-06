#include "MainHUD.h"

#include "Client_Define.h"
#include "UI.h"
#include "TimerUI.h"
#include "TextRenderer.h"

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
	//_UIs.push_back(_timer);
}

void MainHUD::Update(const float& deltaTime)
{
}

void MainHUD::LateUpdate(const float& deltaTime)
{
}