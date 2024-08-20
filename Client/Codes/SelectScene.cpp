#include "SelectScene.h"

#include "Client_Define.h"

#include "SelectButtons.h"
//UHD
#include "HPHUD.h"

int SelectScene::Update(const float& deltaTime)
{
    return 0;
}

int SelectScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool SelectScene::Initialize()
{
    Sound::StopSound((int)SoundGroup::BGM);
    Sound::PlaySound("Bgm_Sound_BGM_Select_Stage", (int)SoundGroup::BGM, 0.5f,true);
    Sound::PlaySound("Effect_Sound_FX_Stage_Select_Entry", (int)SoundGroup::SFX, 0.8f, false);
    UIInitialize();

    return true;
}

void SelectScene::Free()
{
}

bool SelectScene::UIInitialize()
{
    //컴포넌트(배경)
    Engine::GameObject* pBackObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pBackObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pBackObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);

    //스테이지 선택 버튼 (추후 변경 예정
    Engine::GameObject* pButtonObj = Engine::GameObject::Create();
    pButtonObj->AddComponent<SelectButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectBack", pBackObj); pBackObj->SetRenderGroup((int)RenderGroup::BackGround);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectButton", pButtonObj); pButtonObj->SetRenderGroup((int)RenderGroup::UI);
   // Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectHUD", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::UI);

    return true;
}

SelectScene* SelectScene::Create()
{
    return new SelectScene;
}