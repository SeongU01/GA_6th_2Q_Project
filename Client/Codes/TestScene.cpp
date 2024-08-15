#include "TestScene.h"
#include "CardManager.h"
#include "DataManager.h"
#include "CollisionManager.h"
#include "Client_Define.h"

// Component
#include "Mouse.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "DeckSystem.h"
#include "TimerHUD.h"
#include "GridEffect.h"
#include "TopHUD.h"
#include "MPHUD.h"

#include "TimerSystem.h"
//object
#include "Map.h"
#include "TimerUI.h"
#include "Zero.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"
#include "EnemySpawner.h"

int TestScene::Update(const float& deltaTime)
{
    return 0;
}

int TestScene::LateUpdate(const float& deltaTime)
{
    _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"), 
                                       Engine::FindObjectList((int)LayerGroup::Object, L"Card"));

    _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"),
                                       Engine::FindObjectList((int)LayerGroup::Enemy, L"Monster"));

    return 0;
}

bool TestScene::UIinitialize()
{
    Engine::GameObject* pGameObject = Engine::GameObject::Create();
    pGameObject->AddComponent<DeckSystem>();
    pGameObject->SetRenderGroup((int)RenderGroup::UI);
    pGameObject->transform.position = Vector3(1750.f, 950.f, 0.f);

    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pGameObject);

    Engine::GameObject* pTimerObj = Engine::GameObject::Create();
    pTimerObj->AddComponent<TimerHUD>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pTimerObj); pTimerObj->SetRenderGroup((int)RenderGroup::UI);

    Engine::GameObject* pHPHUDDObj = Engine::GameObject::Create();
    pHPHUDDObj->AddComponent<TopHUD>(Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>()->GetPlayerHPComponent(), 0);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"PlayerHP", pHPHUDDObj); pHPHUDDObj->SetRenderGroup((int)RenderGroup::UI);
    
    //¸¶³ª ¹Ù
    Engine::GameObject* pMPHUDDObj = Engine::GameObject::Create();
    pMPHUDDObj->AddComponent<MPHUD>(Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>()->GetPlayerMPComponent(), 0);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"PlayerMP", pMPHUDDObj); pMPHUDDObj->SetRenderGroup((int)RenderGroup::UI);

    return true;
}

bool TestScene::Initialize()
{
    __super::Initialize();
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    ObjectArrangeInfo stage1Obj = DataManager::GetInstance()->GetObjectInfo(L"Stage1");
    EnemySpawnInfo stage1Enemy = DataManager::GetInstance()->GetEnemySpawnInfo(L"Stage1");
    
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1,Vector3(WINCX>>1,WINCY>>1,0.f)));

    MakeObject(stage1Obj);
    
    //EnemySpawner
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"EnemySpawner", EnemySpawner::Create(stage1Enemy));

    // BackGround
    Engine::GameObject* pObject = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pObject->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pObject->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    pObject->SetRenderGroup((int)RenderGroup::BackGround);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"BackGround", pObject);


    pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>((int)stage1.width, (int)stage1.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);


    UIinitialize();

    return true;
}

void TestScene::Free()
{
    SafeRelease(_pCollisionManager);
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
