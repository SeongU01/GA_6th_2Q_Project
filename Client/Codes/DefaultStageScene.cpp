#include "DefaultStageScene.h"
#include "CardManagement.h"
#include "CardSystem.h"
#include "DataManager.h"
#include "CollisionManager.h"

// Component
#include "Mouse.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "DeckSystem.h"

//object
#include "Map.h"
#include "TimerUI.h"
#include "TestPlayer.h"
#include "Obstacle.h"
#include "TestEnemy.h"
#include "Enemy.h"

#include "Client_Define.h"

void DefaultStageScene::Free()
{
}

void DefaultStageScene::MakeObject(ObjectArrangeInfo& objInfo)
{
  for (auto obj : objInfo.objectPositionInfo)
  {
    //ID별로 object 그리드에 생성
    switch (obj.first)
    {
    case 2:
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Mountain",
        Obstacle::Create(
          std::pair(Vector3(obj.second.x, obj.second.y, 0.f), Vector3(obj.second.x + 1.f, obj.second.y, 0.f)),
          L"Obstacle_Mountain")
      );
      break;
    case 99:
      Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create(Vector3(obj.second.x, obj.second.y, 0.f)));
    }
  }
}

int DefaultStageScene::Update(const float& deltaTime)
{
    return 0;
}

int DefaultStageScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool DefaultStageScene::Initialize()
{
    return false;
}
