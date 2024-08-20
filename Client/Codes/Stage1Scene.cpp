#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Client_Define.h"

// Object
#include "GridEffect.h"
#include "Map.h"
#include "EnemySpawner.h"

// Component
#include "SpawnEnemy.h"

#include "Client_Define.h"

bool Stage1Scene::Initialize()
{   
    DataManager* pDataManager = DataManager::GetInstance();

    const MapInfo& stageInfo = pDataManager->GetMapInfo(L"Stage1");
    const ObjectArrangeInfo& objectInfo = pDataManager->GetObjectInfo(L"Stage1");
    const EnemySpawnInfo& enemySpawnInfo = pDataManager->GetEnemySpawnInfo(L"Stage1");

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

    // ½ºÆ÷´×Ç®
    _pEnemySpawner = EnemySpawner::Create(enemySpawnInfo);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Spawner", _pEnemySpawner);    

    Sound::StopSound((int)SoundGroup::BGM);
    //Sound::PlaySound("Bgm_Sound_BGM_Battle_Stage_1", (int)SoundGroup::BGM, 0.8f, true);
    Sound::StopSound((int)SoundGroup::Voice);
    Sound::PlaySound("Voice_Sound_Voice_Zero_Begin_Game", (int)SoundGroup::Voice, 0.8f, false);
    _pScene = Stage2Scene::Create();

    return true;
}

Stage1Scene* Stage1Scene::Create()
{
    return new Stage1Scene;
}