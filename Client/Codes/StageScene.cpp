#include "StageScene.h"

//ui
#include "MainStageHUD.h"
#include "GameOverHUD.h"
#include "GameClearHUD.h"

//ÀÌµ¿°¡´É ¾À
#include "SelectScene.h"
#include "TitleScene.h"

#include "Client_Define.h"
#include "MapManager.h"


int StageScene::Update(const float& deltaTime)
{
    return 0;
}

int StageScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool StageScene::Initialize()
{
    std::wstring path = rootPath;
    MapManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = MapManager::GetInstance()->GetMapInfo(L"Stage1");

    return true;
}

void StageScene::Free()
{
}

StageScene* StageScene::Create()
{
    return new StageScene;
}