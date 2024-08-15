#include "TitleScene.h"

#include "Client_Define.h"
//component
#include "UIComponent.h"
#include "TitleButtons.h"
#include "SpriteRenderer.h"
//UHD
#include "CreditHUD.h"
#include "InfoHUD.h"

int TitleScene::Update(const float& deltaTime)
{
    if (Input::IsKeyDown(DIK_ESCAPE))
    {
        InfoHUD* pInfo = Engine::FindObject((int)LayerGroup::UI, L"Info", NULL)->GetComponent<InfoHUD>();
        pInfo->SetActives(false);

        CreditHUD* pCredit = Engine::FindObject((int)LayerGroup::UI, L"Credit", NULL)->GetComponent<CreditHUD>();
        pCredit->SetActives(false);
    }
    return 0;
}

int TitleScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool TitleScene::Initialize()
{
    Sound::PlaySound("Bgm_Sound_BGM_Title", (int)SoundGroup::BGM, 0.8f, true);
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
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::BackGround);
    //버튼 (4개)
    Engine::GameObject* pButtonObj = Engine::GameObject::Create();
    pButtonObj->AddComponent<TitleButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pButtonObj); pButtonObj->SetRenderGroup((int)RenderGroup::UI);
    //크레딧 팝업
    Engine::GameObject* pCreditObj = Engine::GameObject::Create();
    pCreditObj->AddComponent<CreditHUD>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Credit", pCreditObj); pCreditObj->SetRenderGroup((int)RenderGroup::Fade); //팝업이라 더 높게..
    //정보보기 팝업
    Engine::GameObject* pInfoObj = Engine::GameObject::Create();
    pInfoObj->AddComponent<InfoHUD>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Info", pInfoObj); pInfoObj->SetRenderGroup((int)RenderGroup::Fade);
    return false;
}
void TitleScene::Free()
{
}

TitleScene* TitleScene::Create()
{
    return new TitleScene;
}