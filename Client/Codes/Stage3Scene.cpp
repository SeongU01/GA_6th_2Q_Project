#include "Stage3Scene.h"
#include "Stage4Scene.h"
#include "Client_Define.h"

// Object
#include "GridEffect.h"
#include "Map.h"
#include "EnemySpawner.h"

// Component
#include "SpawnEnemy.h"
#include "CardSystem.h"

#include "Client_Define.h"
#include "EventManager.h"

bool Stage3Scene::Initialize()
{
    DataManager* pDataManager = DataManager::GetInstance();

    const MapInfo& stageInfo = pDataManager->GetMapInfo(L"Stage3");
    const ObjectArrangeInfo& objectInfo = pDataManager->GetObjectInfo(L"Stage3");
    const EnemySpawnInfo& enemySpawnInfo = pDataManager->GetEnemySpawnInfo(L"Stage3");

    // ¸Ê ¹èÄ¡
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stageInfo, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));

    // ±×¸®µå ÀÌÆåÆ®
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>((int)stageInfo.width, (int)stageInfo.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);

    __super::Initialize();    

    MakeObject(objectInfo);

    Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<CardSystem>()->ResetCardInfo();

    // ½ºÆ÷´×Ç®
    _pEnemySpawner = EnemySpawner::Create(enemySpawnInfo);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Spawner", _pEnemySpawner);

    Sound::StopSound((int)SoundGroup::BGM);
    //Sound::PlaySound("Bgm_Sound_BGM_Battle_Stage_1", (int)SoundGroup::BGM, 0.8f, true);

    _pScene = Stage3Scene::Create();

    EventManager::GetInstance()->SetCurrentStage(Stage::Stage3);

    return true;
}

Stage3Scene* Stage3Scene::Create()
{
    return new Stage3Scene;
}