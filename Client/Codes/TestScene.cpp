#include "TestScene.h"
#include "GameObject.h"
#include "Client_Define.h"
#include "TestPlayer.h"
#include "RigidBody2D.h"

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
    TestPlayer* pTestPlayer = TestPlayer::Create();

    Camera::SetTarget(pTestPlayer->GetTransform());
    Camera::SetMaxPosition(Vector3(WINCX, WINCY, 0.f));
    Camera::SetArea(Vector3(WINCX, WINCY, 0.f));
    Engine::AddObjectInLayer((int)LayerGroup::Object, "Test", pTestPlayer);

    return true;
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
