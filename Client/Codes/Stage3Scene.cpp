#include "Stage3Scene.h"
#include "Stage4Scene.h"
#include "Client_Define.h"

//object
#include "GridEffect.h"
#include "Map.h"
#include "EnemySpawner.h"

bool Stage3Scene::Initialize()
{
    DataManager* pDataManager = DataManager::GetInstance();

    const MapInfo& stageInfo = pDataManager->GetMapInfo(L"Stage3");
    const ObjectArrangeInfo& objectInfo = pDataManager->GetObjectInfo(L"Stage3");
    const EnemySpawnInfo& enemySpawnInfo = pDataManager->GetEnemySpawnInfo(L"Stage3");

    // ¸Ê ¹èÄ¡
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stageInfo, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    __super::Initialize();

    // ±×¸®µå ÀÌÆåÆ®
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>((int)stageInfo.width, (int)stageInfo.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);

    MakeObject(objectInfo);

    // ½ºÆ÷´×Ç®
    _pEnemySpawner = EnemySpawner::Create(enemySpawnInfo);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Spawner", _pEnemySpawner);

    Sound::StopSound((int)SoundGroup::BGM);
    //Sound::PlaySound("Bgm_Sound_BGM_Battle_Stage_1", (int)SoundGroup::BGM, 0.8f, true);

    _pScene = Stage3Scene::Create();

    return true;
}

Stage3Scene* Stage3Scene::Create()
{
    return new Stage3Scene;
}