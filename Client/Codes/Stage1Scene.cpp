#include "Stage1Scene.h"

#include "Client_Define.h"
//Component
#include "CardManagement.h"
#include "SpriteRenderer.h"
#include "DataManager.h"
#include "TimerSystem.h"
#include "GameClearButtons.h"
#include "GameOverButtons.h"
//UHD
#include "TimerHUD.h"
#include "GameOverHUD.h"
#include "GameClearHUD.h"
//object
#include "Map.h"
#include "TestPlayer.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"
int Stage1Scene::Update(const float& deltaTime)
{
    //테스트용 코드(게임오버, 클리어 팝업 체크
    if (Input::IsKeyDown(DIK_1))
    {
        Engine::GameObject* pOver = Engine::FindObject((int)LayerGroup::UI, L"GameOver", NULL);
        pOver->GetComponent<GameOverHUD>()->SetActives(true);
        pOver->GetComponent<GameOVerButtons>()->SetActives(true);
    }
    else if (Input::IsKeyDown(DIK_2))
    {
        Engine::GameObject* pClear = Engine::FindObject((int)LayerGroup::UI, L"GameClear", NULL);
        pClear->GetComponent<GameClearHUD>()->SetActives(true);
        pClear->GetComponent<GameClearButtons>()->SetActives(true);
    }
    else if (Input::IsKeyDown(DIK_3))
    {
        Engine::GameObject* pOver = Engine::FindObject((int)LayerGroup::UI, L"GameOver", NULL);
        pOver->GetComponent<GameOverHUD>()->SetActives(false);
        pOver->GetComponent<GameOVerButtons>()->SetActives(false);

        Engine::GameObject* pClear = Engine::FindObject((int)LayerGroup::UI, L"GameClear", NULL);
        pClear->GetComponent<GameClearHUD>()->SetActives(false);
        pClear->GetComponent<GameClearButtons>()->SetActives(false);
    }
    return 0;
}

int Stage1Scene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool Stage1Scene::Initialize()
{
    //Timer=======================
    Engine::GameObject* pTimer = Engine::FindObject((int)LayerGroup::UI, L"TimerSystem", NULL);
    if (pTimer == nullptr) {
        pTimer = Engine::GameObject::Create();
        _pTimerSystem = pTimer->AddComponent<TimerSystem>();
        Engine::AddObjectInLayer((int)LayerGroup::UI, L"TimerSystem", pTimer); pTimer->SetRenderGroup((int)RenderGroup::UI);
    }
    //============================
    std::wstring path = rootPath;
    _pDataManager = DataManager::GetInstance();
    _pDataManager->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = _pDataManager->GetMapInfo(L"Stage1");
    if(Engine::FindObject((int)LayerGroup::Tile, L"Tile", NULL)==nullptr)
        Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    
    if (Engine::FindObject((int)LayerGroup::Player, L"Player", NULL) == nullptr)
        Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create({ 1.0f,1.0f,1.0f }));
    else 
    {
        Engine::GameObject* pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL);
        pPlayer->GetComponent<Player>()->ResetPlayer({ 1.0f,1.0f,1.0f });
        pPlayer->SetActive(true);
    }
 
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Mountain1", Obstacle::Create(std::pair(Vector3(7.f, 0.f, 0.f), Vector3(8.f, 0.f, 0.f)), Vector3(10.f, 0.f, 0.f), L"Obstacle_Mountain"));
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"water", Obstacle::Create(std::pair(Vector3(6.f, 1.f, 0.f), Vector3(10.f, 0.f, 0.f)), Vector3(8.f, 3.f, 0.f)));
    TestEnemy* monster = TestEnemy::Create(); Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Enemy", monster); monster->GetComponent<Enemy>()->SetGridPosition({ 0,1,0 });

    _pCardManagement = CardManagement::GetInstance();
    _pCardManagement->LoadCard((path + L"Data/Card").c_str());

    UIInitialize();
    return true;
}

bool Stage1Scene::UIInitialize()
{
    //컴포넌트(배경)
    Engine::GameObject* pHUDObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pHUDObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pHUDObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::BackGround);
    //타이머
    Engine::GameObject* pTimerObj = Engine::GameObject::Create();
    pTimerObj->AddComponent<TimerHUD>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pTimerObj); pTimerObj->SetRenderGroup((int)RenderGroup::UI);
    //게임오버 팝업
    Engine::GameObject* pGameOverObj = Engine::GameObject::Create();
    pGameOverObj->AddComponent<GameOverHUD>();
    pGameOverObj->AddComponent<GameOVerButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"GameOver", pGameOverObj); pGameOverObj->SetRenderGroup((int)RenderGroup::Fade); //팝업이라 더 높게..
    //게임클리어 팝업
    Engine::GameObject* pGameClearObj = Engine::GameObject::Create();
    pGameClearObj->AddComponent<GameClearHUD>();
    pGameClearObj->AddComponent<GameClearButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"GameClear", pGameClearObj); pGameClearObj->SetRenderGroup((int)RenderGroup::Fade);
    return false;
}

void Stage1Scene::Free()
{
}

Stage1Scene* Stage1Scene::Create()
{
    return new Stage1Scene;
}