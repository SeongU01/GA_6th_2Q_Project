#include "Stage1Scene.h"
#include "CutScene.h"
#include "Client_Define.h"

// Object
#include "GridEffect.h"
#include "Map.h"
#include "EnemySpawner.h"

// Component
#include "SpawnEnemy.h"
#include "CardSystem.h"
#include "TextRenderer.h"

#include "EventManager.h"
#include "Client_Define.h"

bool Stage1Scene::Initialize()
{   
    DataManager* pDataManager = DataManager::GetInstance();

    const MapInfo& stageInfo = pDataManager->GetMapInfo(L"Stage1");
    const ObjectArrangeInfo& objectInfo = pDataManager->GetObjectInfo(L"Stage1");
    const EnemySpawnInfo& enemySpawnInfo = pDataManager->GetEnemySpawnInfo(L"Stage1");

    // 맵 배치
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stageInfo, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));

    // 그리드 이펙트
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"GridEffect");
    pObject->AddComponent<GridEffect>((int)stageInfo.width, (int)stageInfo.height);
    pObject->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pObject);
    
    __super::Initialize();

    MakeObject(objectInfo);

    Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<CardSystem>()->ResetCardInfo();

    // 스포닝풀
    _pEnemySpawner = EnemySpawner::Create(enemySpawnInfo);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Spawner", _pEnemySpawner);

    Sound::StopSound((int)SoundGroup::BGM);
    Sound::PlaySound("Bgm_Sound_BGM_Battle_Stage_1", (int)SoundGroup::BGM, 0.5f, true);
    Sound::PlaySound("Voice_Sound_Voice_Zero_Begin_Game", (int)SoundGroup::Voice, 0.8f, false);
    Sound::PlaySound("Effect_Sound_FX_Stage_Battle_Entry", (int)SoundGroup::SFX, 0.8f, false);
    
    Engine::GameObject* pUI = Engine::GameObject::Create();
    pUI->SetRenderGroup((int)RenderGroup::UI);
    Engine::TextRenderer* pTextRenderer = pUI->AddComponent<Engine::TextRenderer>(L"TextRenderer", 0XFFFFFF, 25.f, DWRITE_FONT_WEIGHT_BOLD);
    pTextRenderer->SetText(L"스테이지 1");
    pTextRenderer->SetDrawRect(200.f, 100.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pUI);
    pUI->transform.position = Vector3(1770.f, 20.f, 0.f);

    _pScene = CutScene::Create(2);

    return true;
}

int Stage1Scene::Update(const float& deltaTime)
{
    __super::Update(deltaTime);
    
    _elapsed += deltaTime;

    if (!_isTutorial)
    {
        if (1.f <= _elapsed)
        {
            EventManager::GetInstance()->Tutorial1();
            _isTutorial = true;
        }
    }

    return 0;
}

Stage1Scene* Stage1Scene::Create()
{
    return new Stage1Scene;
}