#include "TestScene.h"
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
  (
    (int)LayerGroup::Tile, "Tile",
    Map::Create(Vector3(20.f, 8.f, 0.f), Vector3(10.f, 10.f, 0.f),Vector3(100.f,100.f,0.f))
  );
  Engine::AddObjectInLayer
  (
      (int)LayerGroup::UI, "MainUI",
      Canvas::Create("Main")
  );
  Engine::AddObjectInLayer(
      (int)LayerGroup::UI, "TimerText",
      TimerUI::Create()
  );

  return true;
}

TestScene* TestScene::Create()
{
    return new TestScene;
}
