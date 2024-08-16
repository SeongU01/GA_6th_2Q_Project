#include "Stage2Scene.h"
#include "Client_Define.h"

// Object
#include "GridEffect.h"
#include "Map.h"
#include "EnemySpawner.h"

// Manager
#include "DataManager.h"
#include "CollisionManager.h"

bool Stage2Scene::Initialize()
{
    __super::Initialize();

    DataManager* pDataManager = DataManager::GetInstance();

    const MapInfo& stageInfo = pDataManager->GetMapInfo(L"Stage2");
    const ObjectArrangeInfo& objectInfo = pDataManager->GetObjectInfo(L"Stage2");
    const EnemySpawnInfo& enemySpawnInfo = pDataManager->GetEnemySpawnInfo(L"Stage2");

    // ¸Ê ¹èÄ¡
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stageInfo, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    MakeObject(objectInfo);

    // ½ºÆ÷´×Ç®
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Spawner", EnemySpawner::Create(enemySpawnInfo));

    // ±×¸®µå ÀÌÆåÆ®
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>((int)stageInfo.width, (int)stageInfo.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);

    Sound::StopSound((int)SoundGroup::BGM);
    //Sound::PlaySound("Bgm_Sound_BGM_Battle_Stage_1", (int)SoundGroup::BGM, 0.8f, true);

    return true;
}

Stage2Scene* Stage2Scene::Create()
{
    return new Stage2Scene;
}