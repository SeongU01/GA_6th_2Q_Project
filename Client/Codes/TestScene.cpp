#include "TestScene.h"
#include "GameObject.h"
#include "Client_Define.h"

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
    Engine::GameObject* pGameObject = Engine::GameObject::Create();
    pGameObject->SetRenderGroup((int)RenderGroup::BackGround);

    pGameObject->GetTransform()->position = Vector3(100.f, 100.f, 100.f);
    pGameObject->GetTransform()->position += Vector3(100.f, 100.f, 100.f);

    Engine::AddObjectInLayer((int)LayerGroup::Object, "Test", pGameObject);

    return true;
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
