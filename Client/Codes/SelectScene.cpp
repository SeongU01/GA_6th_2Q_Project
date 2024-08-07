#include "SelectScene.h"

//ui
#include "StageSelectHUD.h"
//�̵����� ��
#include "StageScene.h"

#include "MapManager.h"
#include "Map.h"
#include "TestPlayer.h"

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
    MapInfo stage1 = MapManager::GetInstance()->GetMapInfo(L"Stage2");
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    
    TestPlayer* pPlayer = static_cast<TestPlayer*>(Engine::FindObject((int)LayerGroup::Player, L"Player",NULL));
    pPlayer->ChangeCurrentGrid();
    
    
    return true;
}

void SelectScene::Free()
{
}

SelectScene* SelectScene::Create()
{
    return new SelectScene;
}