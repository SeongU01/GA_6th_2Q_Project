#include "Stage2Scene.h"
#include "Client_Define.h"
#include "DataManager.h"
//object
#include "Map.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"

int Stage2Scene::Update(const float& deltaTime)
{
    __super::Update(deltaTime);
    return 0;
}

int Stage2Scene::LateUpdate(const float& deltaTime)
{
    __super::LateUpdate(deltaTime);
    return 0;
}

bool Stage2Scene::Initialize()
{
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    __super::Initialize();
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Mountain1", Obstacle::Create(std::pair(Vector3(7.f, 0.f, 0.f), Vector3(8.f, 0.f, 0.f)), Vector3(10.f, 0.f, 0.f), L"Obstacle_Mountain"));
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"water", Obstacle::Create(std::pair(Vector3(6.f, 1.f, 0.f), Vector3(10.f, 0.f, 0.f)), Vector3(8.f, 3.f, 0.f)));
    TestEnemy* monster = TestEnemy::Create(); Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Enemy", monster); monster->GetComponent<Enemy>()->SetGridPosition({ 0,1,0 });
    return true;
}

bool Stage2Scene::UIinitialize()
{
    __super::UIinitialize();
    return false;
}


void Stage2Scene::Free()
{
    __super::Free();
}

Stage2Scene* Stage2Scene::Create()
{
    return new Stage2Scene;
}