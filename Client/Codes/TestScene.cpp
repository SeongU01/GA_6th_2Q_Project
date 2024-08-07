#include "TestScene.h"
#include "CardManagement.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "Client_Define.h"
#include "MapManager.h"
//ui
#include "Canvas.h"

//object
#include "MapManager.h"
#include "Map.h"
#include "TimerUI.h"
#include "TestPlayer.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"

int TestScene::Update(const float& deltaTime)
{
    return 0;
}

int TestScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool TestScene::Initialize()
{
    std::wstring path = rootPath;
    MapManager::GetInstance()->LoadMap((path + L"Data/Map").c_str());
    MapInfo stage1 = MapManager::GetInstance()->GetMapInfo(L"Stage1");

    /*Engine::AddObjectInLayer
    ((int)LayerGroup::Tile, L"Tile", 
        Map::Create(Vector3(stage1.width, stage1.height, 0.f), Vector3(stage1.tileOffsetX, stage1.tileOffsetY, 0.f)
          ,Vector3(WINCX>>1,WINCY>>1,0.f),stage1.mapOffsetY));*/
    Engine::AddObjectInLayer((int)LayerGroup::Tile, L"Tile", Map::Create(stage1,Vector3(WINCX>>1,WINCY>>1,0.f)));


    Engine::AddObjectInLayer((int)LayerGroup::UI, L"MainUI", Canvas::Create(L"Main"));
    Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create());
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Mountain1", 
      Obstacle::Create(std::pair(Vector3(7.f,0.f,0.f), Vector3(8.f,0.f, 0.f)),L"Obstacle_Mountain"));

    Engine::AddObjectInLayer((int)LayerGroup::Object, L"water", 
    Obstacle::Create(std::pair(Vector3(6.f,1.f,0.f), Vector3(8.f,3.f, 0.f))));
    TestEnemy* monster = TestEnemy::Create(); Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Enemy", monster); monster->GetComponent<Enemy>()->SetGridPosition({ 0,1,0 });
   
    _pCardManagement = CardManagement::GetInstance();
    _pCardManagement->LoadCard((path + L"Data/Card").c_str());
    

    Engine::GameObject* pBackGround = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pBackGround->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pBackGround->GetTransform()->SetPosition(Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f));
    pBackGround->SetRenderGroup((int)RenderGroup::BackGround);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"BackGround", pBackGround);

    return true;
}

void TestScene::Free()
{
    SafeRelease(_pCardManagement);
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
