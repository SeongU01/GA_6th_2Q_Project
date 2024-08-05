#include "TestScene.h"
#include "CardSystem.h"
#include "TextRenderer.h"
#include "Client_Define.h"

//ui
#include "Canvas.h"

//object
#include "Map.h"
#include "TextRenderer.h"
#include "TimerUI.h"

void TestScene::Free()
{
}

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
        Map::Create(Vector3(20.f, 8.f, 0.f), Vector3(10.f, 10.f, 0.f),Vector3(100.f,100.f,0.f)));
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"MainUI", Canvas::Create(L"Main"));
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"TimerText", TimerUI::Create());

    CardSystem* pCardSystem = CardSystem::GetInstance();
    std::wstring path = rootPath;

    pCardSystem->LoadCard((path + L"Data/Card").c_str());

    Engine::GameObject* pGameObject = Engine::GameObject::Create();
    Engine::TextRenderer* pTextRenderer = pGameObject->AddComponent<Engine::TextRenderer>(L"TextRenderer");
    pTextRenderer->SetTextLayout(pCardSystem->_texts[0].c_str(), 500.f, 300.f);

    pGameObject->SetRenderGroup(0);
    Engine::AddObjectInLayer((int)LayerGroup::Object, L"Test", pGameObject);

  return true;
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
