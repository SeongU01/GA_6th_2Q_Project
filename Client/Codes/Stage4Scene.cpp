#include "Stage4Scene.h"

#include "Client_Define.h"
//Component
#include "CardManagement.h"
#include "SpriteRenderer.h"
#include "DataManager.h"
#include "TimerSystem.h"
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

int Stage4Scene::Update(const float& deltaTime)
{
    return 0;
}

int Stage4Scene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool Stage4Scene::Initialize()
{
    //Timer=======================
    Engine::GameObject* pTimer = Engine::GameObject::Create();
    _pTimerSystem = pTimer->AddComponent<TimerSystem>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"TimerSystem", pTimer); pTimer->SetRenderGroup((int)RenderGroup::UI);
    //============================
    std::wstring path = rootPath;
    DataManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");

    /*Engine::AddObjectInLayer
    ((int)LayerGroup::Tile, L"Tile",
        Map::Create(Vector3(stage1.width, stage1.height, 0.f), Vector3(stage1.tileOffsetX, stage1.tileOffsetY, 0.f)
          ,Vector3(WINCX>>1,WINCY>>1,0.f),stage1.mapOffsetY));*/
    //Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));

    ////Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create());
    //Engine::AddObjectInLayer((int)LayerGroup::Object, L"Mountain1", Obstacle::Create(std::pair(Vector3(7.f, 0.f, 0.f), Vector3(8.f, 0.f, 0.f)), L"Obstacle_Mountain"));
    //Engine::AddObjectInLayer((int)LayerGroup::Object, L"water", Obstacle::Create(std::pair(Vector3(6.f, 1.f, 0.f), Vector3(8.f, 3.f, 0.f))));
    //TestEnemy* monster = TestEnemy::Create(); Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Enemy", monster); monster->GetComponent<Enemy>()->SetGridPosition({ 0,1,0 });

    //_pCardManagement = CardManagement::GetInstance();
    //_pCardManagement->LoadCard((path + L"Data/Card").c_str());

    UIInitialize();
    return true;
}

bool Stage4Scene::UIInitialize()
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
    return false;
}

void Stage4Scene::Free()
{
    SafeRelease(_pCardManagement);
}

Stage4Scene* Stage4Scene::Create()
{
    return new Stage4Scene;
}