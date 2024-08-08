#include "SelectScene.h"


//�̵����� ��

#include "DataManager.h"
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
    DataManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = DataManager::GetInstance()->GetMapInfo(L"Stage2");
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    
    TestPlayer* pPlayer = static_cast<TestPlayer*>(Engine::FindObject((int)LayerGroup::Player, L"Player",NULL));
    pPlayer->ChangeCurrentGrid();
   // UIFrame = ((int)LayerGroup::UI, L"MainUI", NULL);
    UIInitialize();
    return true;
}

void SelectScene::Free()
{
}

bool SelectScene::UIInitialize()
{
    Engine::GameObject* pObj = Engine::GameObject::Create();
    //pObj->AddComponent<>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pObj);
    return false;
}

SelectScene* SelectScene::Create()
{
    return new SelectScene;
}