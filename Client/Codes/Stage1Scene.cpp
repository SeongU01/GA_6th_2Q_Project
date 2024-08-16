#include "Stage1Scene.h"
#include "Client_Define.h"

// Object
#include "GridEffect.h"
#include "Map.h"
#include "EnemySpawner.h"

// Component
#include "SpawnEnemy.h"

// Manager
#include "DataManager.h"
#include "CardManager.h"
#include "CollisionManager.h"

int Stage1Scene::LateUpdate(const float& deltaTime)
{
    if (_pEnemySpawner->GetComponent<SpawnEnemy>()->CheckStageEnd())
    {
        if (!_isSelectCard)
        {
            _isSelectCard = true;
            CardManager::GetInstance()->StartSelectCardScene();
        }
    }

    __super::LateUpdate(deltaTime);

    return 0;
}

bool Stage1Scene::Initialize()
{   
    DataManager* pDataManager = DataManager::GetInstance();

    const MapInfo& stageInfo = pDataManager->GetMapInfo(L"Stage1");
    const ObjectArrangeInfo& objectInfo = pDataManager->GetObjectInfo(L"Stage1");
    const EnemySpawnInfo& enemySpawnInfo = pDataManager->GetEnemySpawnInfo(L"Stage1");

    // �� ��ġ
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stageInfo, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    __super::Initialize();
    MakeObject(objectInfo);

    // ������Ǯ
    _pEnemySpawner = EnemySpawner::Create(enemySpawnInfo);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Spawner", _pEnemySpawner);

    // �׸��� ����Ʈ
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>((int)stageInfo.width, (int)stageInfo.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);

    Sound::StopSound((int)SoundGroup::BGM);
    //Sound::PlaySound("Bgm_Sound_BGM_Battle_Stage_1", (int)SoundGroup::BGM, 0.8f, true);

    return true;
}

Stage1Scene* Stage1Scene::Create()
{
    return new Stage1Scene;
}