#include "TitleScene.h"
#include "Client_Define.h"

//component
#include "UIComponent.h"
#include "TitleButtons.h"
#include "SpriteRenderer.h"
#include "Animation.h"

//UHD
#include "CreditHUD.h"
#include "InfoHUD.h"

#include "DataManager.h"
#include "CardManager.h"

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
    if (_pAnimation->IsLastFrame())
    {
        if (_isRevers)
            _isRevers = false;
        else
            _isRevers = true;
        
        _pAnimation->SetLastFrame();
        _pAnimation->SetReversePlay(_isRevers);
    }

    return 0;
}

bool TitleScene::Initialize()
{
    // 공통 데이터
    std::wstring filePath = rootPath;
    DataManager* pDataManager = DataManager::GetInstance();
    pDataManager->LoadToolTip((filePath + L"Data/ToolTip").c_str());
    pDataManager->LoadCutScene((filePath + L"Data/CutScene").c_str());
    pDataManager->LoadEnemySpawn((filePath + L"Data/Wave").c_str());
    pDataManager->LoadMap((filePath + L"Data/Map").c_str());
    pDataManager->LoadObjectArrange((filePath + L"Data/ObjectArrange").c_str());
    pDataManager->LoadAttackRangeData((filePath + L"Data/Card").c_str());

    // 카드 데이터
    CardManager* pCardManager = CardManager::GetInstance();
    pCardManager->LoadCard((filePath + L"Data/Card").c_str());
    pCardManager->SetDontDestroyObject(true);
    pCardManager->SetRenderGroup((int)RenderGroup::None);

    Engine::AddObjectInLayer((int)LayerGroup::UI, L"", pCardManager);

    Sound::PlaySound("Bgm_Sound_BGM_Title", (int)SoundGroup::BGM, 0.5f, true);

    Engine::GameObject* pGameObject = Engine::GameObject::Create();
    pGameObject->transform.position = Vector3(WINCX >> 1, WINCY >> 1, 0.f);
    _pAnimation = pGameObject->AddComponent<Engine::Animation>(L"Animation");
    _pFirefly = pGameObject->AddComponent<Engine::Animation>(L"Firefly");
    _pFirefly->LoadAnimation(L"Title_Title");
    _pFirefly->ChangeAnimation(L"Firefly");
    _pAnimation->LoadAnimation(L"Title_Title");
    _pAnimation->ChangeAnimation(L"Idle");
    pGameObject->AddComponent<Engine::SpriteRenderer>(L"Firefly")->BindAnimation(_pFirefly);
    pGameObject->GetComponent<Engine::SpriteRenderer>()->BindAnimation(_pAnimation);
    pGameObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pGameObject);

    UIInitialize();

    return true;
}

bool TitleScene::UIInitialize()
{
    //컴포넌트(배경)
    Engine::GameObject* pHUDObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pHUDObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"Title"));
    pSpriteRenderer->SetIndex(0);
    pHUDObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
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

    return true;
}
void TitleScene::Free()
{
}

TitleScene* TitleScene::Create()
{
    return new TitleScene;
}