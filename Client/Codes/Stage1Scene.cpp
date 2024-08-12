#include "Stage1Scene.h"
#include "Client_Define.h"
#include "DataManager.h"
#include "CollisionManager.h"
//object
#include "GridEffect.h"
#include "Map.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"
int Stage1Scene::Update(const float& deltaTime)
{
    __super::Update(deltaTime);
    return 0;
}

int Stage1Scene::LateUpdate(const float& deltaTime)
{
    __super::LateUpdate(deltaTime);
    return 0;
}

bool Stage1Scene::Initialize()
{
/*    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    __super::Initialize();
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Mountain1", Obstacle::Create(std::pair(Vector3(7.f, 0.f, 0.f), Vector3(8.f, 0.f, 0.f)), Vector3(10.f, 0.f, 0.f), L"Obstacle_Mountain"));
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"water", Obstacle::Create(std::pair(Vector3(6.f, 1.f, 0.f), Vector3(10.f, 0.f, 0.f)), Vector3(8.f, 3.f, 0.f)));
    TestEnemy* monster = TestEnemy::Create(); Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Enemy", monster); monster->GetComponent<Enemy>()->SetGridPosition({ 0,1,0 });
   */
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    ObjectArrangeInfo stage1Obj = DataManager::GetInstance()->GetObjectInfo(L"Stage1");
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    __super::Initialize();
    MakeObject(stage1Obj);
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>(stage1.width, stage1.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);

    UIinitialize();
    return true;
}

bool Stage1Scene::UIinitialize()
{
    __super::UIinitialize();
    return false;
}

void Stage1Scene::Free()
{
    __super::Free();
}

Stage1Scene* Stage1Scene::Create()
{
    return new Stage1Scene;
}