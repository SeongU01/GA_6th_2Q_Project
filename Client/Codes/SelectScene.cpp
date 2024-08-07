#include "SelectScene.h"

//ui
#include "StageSelectHUD.h"
//ÀÌµ¿°¡´É ¾À
#include "StageScene.h"

#include "MapManager.h"
#include "Client_Define.h"


int SelectScene::Update(const float& deltaTime)
{
    return 0;
}

int SelectScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool SelectScene::Initialize()
{
    std::wstring path = rootPath;
    MapManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = MapManager::GetInstance()->GetMapInfo(L"Stage1");

    return true;
}

void SelectScene::Free()
{
}

SelectScene* SelectScene::Create()
{
    return new SelectScene;
}