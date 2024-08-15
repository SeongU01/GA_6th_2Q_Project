#include "Stage3Scene.h"
#include "Client_Define.h"
#include "DataManager.h"
//object
#include "GridEffect.h"
#include "Map.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"

int Stage3Scene::Update(const float& deltaTime)
{
    __super::Update(deltaTime);
    return 0;
}

int Stage3Scene::LateUpdate(const float& deltaTime)
{
    __super::LateUpdate(deltaTime);
    return 0;
}

bool Stage3Scene::Initialize()
{
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    ObjectArrangeInfo stage1Obj = DataManager::GetInstance()->GetObjectInfo(L"Stage1");
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    __super::Initialize();
    MakeObject(stage1Obj);
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>((int)stage1.width, (int)stage1.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);

    UIinitialize();
    return true;
}

bool Stage3Scene::UIinitialize()
{
    __super::UIinitialize();
    return false;
}

void Stage3Scene::Free()
{
    __super::Free();
}

Stage3Scene* Stage3Scene::Create()
{
    return new Stage3Scene;
}