#include "MainUHD.h"

#include "Client_Define.h"
#include "UI.h"

MainUHD::MainUHD()
	:MonoBehavior("Main")
{
}

void MainUHD::Awake()
{

}

void MainUHD::Start()
{
	UI::UIInfo info;
	info.position = { 0.f, 0.f, 0.f };
	info.pParent = GetTransform();
	info.textureTag = L"Test";
	info.name = "Timer";
	UI* _timer = UI::Create(info);
	Engine::AddObjectInLayer((int)LayerGroup::UI, "Timer", _timer);
	_UIs.push_back(_timer);
}

void MainUHD::Update(const float& deltaTime)
{
}

void MainUHD::LateUpdate(const float& deltaTime)
{
}