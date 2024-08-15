#include "Stage4Scene.h"
#include "Client_Define.h"
#include "DataManager.h"
//object
#include "Map.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"

int Stage4Scene::Update(const float& deltaTime)
{
    __super::Update(deltaTime);
    return 0;
}

int Stage4Scene::LateUpdate(const float& deltaTime)
{
    __super::LateUpdate(deltaTime);
    return 0;
}


bool Stage4Scene::Initialize()
{
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");
    __super::Initialize();
    
    Sound::StopSound((int)SoundGroup::BGM);
    Sound::PlaySound("Bgm_Sound_BGM_Battle_Stage_4", (int)SoundGroup::BGM, 0.8f, true);

    return true;
}

bool Stage4Scene::UIinitialize()
{
    __super::UIinitialize();
    return false;
}


void Stage4Scene::Free()
{
    __super::Free();
}

Stage4Scene* Stage4Scene::Create()
{
    return new Stage4Scene;
}