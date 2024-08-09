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

//object
#include "Map.h"
#include "TimerUI.h"
#include "TestPlayer.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"

int TestScene::Update(const float& deltaTime)
{
    return 0;
}

int TestScene::LateUpdate(const float& deltaTime)
{
    _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"), 
                                       Engine::FindObjectList((int)LayerGroup::Object, L"Card"));

    return 0;
}

bool TestScene::UIInitialize()
{
    Engine::GameObject* pGameObject = Engine::GameObject::Create();
    pGameObject->AddComponent<DeckSystem>();
    pGameObject->SetRenderGroup((int)RenderGroup::UI);
    pGameObject->transform.position = Vector3(1750.f, 950.f, 0.f);

    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Deck", pGameObject);

    return true;
}

bool TestScene::Initialize()
{
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    ObjectArrangeInfo stage1Obj = DataManager::GetInstance()->GetObjectInfo(L"Stage1");

    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1,Vector3(WINCX>>1,WINCY>>1,0.f)));
    
    MakeObject(stage1Obj);
    
    // BackGround
    Engine::GameObject* pObject = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pObject->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pObject->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    pObject->SetRenderGroup((int)RenderGroup::BackGround);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"BackGround", pObject);

    // Mouse
    pObject = Engine::GameObject::Create();
    pObject->SetName(L"Mouse");
    pObject->SetRenderGroup((int)RenderGroup::UI);
    pObject->AddComponent<Mouse>(L"Mouse");
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Mouse", pObject);

    _pCollisionManager = Engine::CollisionManager::Create();

   UIInitialize();

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
