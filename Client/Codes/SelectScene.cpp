#include "SelectScene.h"

//ui
#include "HPHUD.h"
#include "SelectButtons.h"

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
    //std::wstring path = rootPath;
    //MapManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    //MapInfo stage1 = MapManager::GetInstance()->GetMapInfo(L"Stage2");
    //Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1, Vector3(WINCX >> 1, WINCY >> 1, 0.f)));
    //
    //TestPlayer* pPlayer = static_cast<TestPlayer*>(Engine::FindObject((int)LayerGroup::Player, L"Player",NULL));
    //pPlayer->ChangeCurrentGrid();
   // UIFrame = ((int)LayerGroup::UI, L"MainUI", NULL);
    UIInitialize();
    return true;
}

void SelectScene::Free()
{
}

bool SelectScene::UIInitialize()
{
    //컴포넌트(배경)
    Engine::GameObject* pBackObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pBackObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pBackObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::GameObject* pHUDObj = Engine::GameObject::Create();
    pHUDObj->AddComponent<HPHUD>(); // 체력바
    //스테이지 선택 버튼 (추후 변경 예정
    Engine::GameObject* pButtonObj = Engine::GameObject::Create();
    pButtonObj->AddComponent<SelectButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pBackObj); pBackObj->SetRenderGroup((int)RenderGroup::BackGround);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pButtonObj); pButtonObj->SetRenderGroup((int)RenderGroup::UI);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::UI);
    return false;
}

SelectScene* SelectScene::Create()
{
    return new SelectScene;
}