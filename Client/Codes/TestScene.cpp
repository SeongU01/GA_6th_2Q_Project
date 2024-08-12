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
#include "TimerSystem.h"
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

bool TestScene::UIinitialize()
{
    __super::UIinitialize();
    return false;
}

bool TestScene::Initialize()
{
    __super::Initialize();
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    ObjectArrangeInfo stage1Obj = DataManager::GetInstance()->GetObjectInfo(L"Stage1");
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1,Vector3(WINCX>>1,WINCY>>1,0.f)));
    MakeObject(stage1Obj);

    _pCollisionManager = Engine::CollisionManager::Create();

    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>(stage1.width, stage1.height);
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
