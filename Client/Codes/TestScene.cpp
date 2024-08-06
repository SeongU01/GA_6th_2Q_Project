#include "TestScene.h"
#include "CardManagement.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "Client_Define.h"

//ui
#include "Canvas.h"

//object
#include "Map.h"
#include "TimerUI.h"
#include "TestPlayer.h"
#include "Obstacle.h"
#include "TestEnemy.h"

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
    Engine::AddObjectInLayer
    ((int)LayerGroup::Tile, L"Tile", 
        Map::Create(Vector3(16.f, 7.f, 0.f), Vector3(10.f, 10.f, 0.f),Vector3(200.f,200.f,0.f)));
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"MainUI", Canvas::Create(L"Main"));
    Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create());
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Test", 
      Obstacle::Create(std::pair(Vector3(7.f,3.f,0.f), Vector3(8.f,3.f, 0.f)),L"Obstacle_Mountain"));
    Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Enemy", TestEnemy::Create());
    
    _pCardManagement = CardManagement::GetInstance();
    std::wstring path = rootPath;

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
