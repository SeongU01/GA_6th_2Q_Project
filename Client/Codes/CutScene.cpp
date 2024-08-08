#include "CutScene.h"

#include "TitleScene.h"

#include "Client_Define.h"
#include "DataManager.h"


int CutScene::Update(const float& deltaTime)
{
    return 0;
}

int CutScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool CutScene::Initialize()
{
    std::wstring path = rootPath;
    DataManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage1");

    return true;
}

void CutScene::Free()
{
}

CutScene* CutScene::Create()
{
    return new CutScene;
}