#include "TestScene.h"
#include "Client_Define.h"

//object
#include "Map.h"

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
  (
    (int)LayerGroup::Tile, "Tile",
    Map::Create(Vector3(10.f, 10.f, 0.f), Vector3(10.f, 10.f, 0.f),Vector3(300.f,100.f,0.f))
  );
    return true;
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
