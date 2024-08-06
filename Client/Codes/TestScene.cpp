#include "TestScene.h"
#include "CardSystem.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "Client_Define.h"

//ui
#include "Canvas.h"

//object
#include "Map.h"
#include "TimerUI.h"
#include "TestPlayer.h"

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
        Map::Create(Vector3(16.f, 7.f, 0.f), Vector3(10.f, 10.f, 0.f),Vector3(250.f,200.f,0.f)));
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"MainUI", Canvas::Create(L"Main"));
    Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create());
    
    _pCardSystem = CardSystem::GetInstance();
    std::wstring path = rootPath;

    _pCardSystem->LoadCard((path + L"Data/Card").c_str());
    
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
    SafeRelease(_pCardSystem);
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
