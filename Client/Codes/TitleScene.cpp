#include "TitleScene.h"
//타이틀 ui (팝업 스크린 ui 포함)

#include "TitleButtons.h"
#include "UIComponent.h"
#include "SpriteRenderer.h"

#include "MapManager.h"
#include "Map.h"
#include "TestPlayer.h"

#include "Client_Define.h"

int TitleScene::Update(const float& deltaTime)
{
    return 0;
}

int TitleScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool TitleScene::Initialize()
{

    UIInitialize();
    return true;
}

bool TitleScene::UIInitialize()
{
    //컴포넌트(배경)
    Engine::GameObject* pHUDObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pHUDObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pHUDObj->transform.position=Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    //버튼 (4개)
    Engine::GameObject* pButtonObj = Engine::GameObject::Create();
    pButtonObj->AddComponent<TitleButtons>();
    
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::BackGround);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pButtonObj); pButtonObj->SetRenderGroup((int)RenderGroup::UI);
    return false;
}
void TitleScene::Free()
{
}

TitleScene* TitleScene::Create()
{
    return new TitleScene;
}