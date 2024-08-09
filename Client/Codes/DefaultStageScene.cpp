#include "DefaultStageScene.h"
//UI
#include "TimerHUD.h"
#include "GameOverHUD.h"
#include "GameOverButtons.h"
#include "GameClearHUD.h"
#include "GameClearButtons.h"
#include "TimerSystem.h"
//object
#include "TestPlayer.h"
#include "Obstacle.h"
#include "Player.h"
#include "Defense.h"

#include "Client_Define.h"

void DefaultStageScene::Free()
{
}

void DefaultStageScene::MakeObject(ObjectArrangeInfo& objInfo)
{
  for (auto obj : objInfo.objectInfos)
  {
    //ID별로 object 그리드에 생성
    switch (obj.objectID)
    {
    case 0:
      //TODO:방어 목표(발전기) object만들면 추가하기
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Defense",
        Defense::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x , obj.objectPosition.y, 0.f)),
          Vector3(0.f, -60.f, 0.f), obj.objectTag,
          L"Defense_Generator")
      );
      break;
    case 1:
      //TODO:방어 목표(방위본부) object만들면 추가하기
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Defense",
        Defense::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x + 1.f, obj.objectPosition.y, 0.f)),
          Vector3(0.f, -80.f, 0.f), obj.objectTag,
          L"Defense_Command")
      );
      break;
    case 2:
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Mountain",
        Obstacle::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x + 1.f, obj.objectPosition.y, 0.f)),
          Vector3(0.f, -50.f, 0.f),
          L"Obstacle_Mountain")
      );
      break;
    case 3:
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Buliding",
        Obstacle::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f)),
          Vector3(0.f, -40.f, 0.f),
          L"Obstacle_Building")
      );
      break;
    case 4:
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Buliding",
        Obstacle::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f)),
          Vector3(0.f, -40.f, 0.f),
          L"Obstacle_BrokenBuilding")
      );
      break;
    case 5:
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Buliding",
        Obstacle::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f)),
          Vector3(0.f, -30.f, 0.f),
          L"Obstacle_Portal")
      );
      break;
    case 6:
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Plant",
        Obstacle::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f)),
          Vector3(0.f, 0.f, 0.f),
          L"Obstacle_Plant1")
      );
      break;
    case 7:
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Plant",
        Obstacle::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f)),
          Vector3(0.f, 0.f, 0.f),
          L"Obstacle_Plant2")
      );
      break;
    case 99:
      Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f)));
      break;
    }
  }
}

int DefaultStageScene::Update(const float& deltaTime)
{
    //테스트용 코드(게임오버, 클리어 팝업 체크
    if (Input::IsKeyDown(DIK_1))
    {
        Engine::GameObject* pOver = Engine::FindObject((int)LayerGroup::UI, L"GameOver", NULL);
        pOver->GetComponent<GameOverHUD>()->SetActives(true);
        pOver->GetComponent<GameOVerButtons>()->SetActives(true);
    }
    else if (Input::IsKeyDown(DIK_2))
    {
        Engine::GameObject* pClear = Engine::FindObject((int)LayerGroup::UI, L"GameClear", NULL);
        pClear->GetComponent<GameClearHUD>()->SetActives(true);
        pClear->GetComponent<GameClearButtons>()->SetActives(true);
    }
    else if (Input::IsKeyDown(DIK_3))
    {
        Engine::GameObject* pOver = Engine::FindObject((int)LayerGroup::UI, L"GameOver", NULL);
        pOver->GetComponent<GameOverHUD>()->SetActives(false);
        pOver->GetComponent<GameOVerButtons>()->SetActives(false);

        Engine::GameObject* pClear = Engine::FindObject((int)LayerGroup::UI, L"GameClear", NULL);
        pClear->GetComponent<GameClearHUD>()->SetActives(false);
        pClear->GetComponent<GameClearButtons>()->SetActives(false);
    }
    return 0;
}

int DefaultStageScene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool DefaultStageScene::Initialize()
{
    //Timer=======================
    Engine::GameObject* pTimer = Engine::GameObject::Create();
    _pTimerSystem = pTimer->AddComponent<TimerSystem>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"TimerSystem", pTimer); pTimer->SetRenderGroup((int)RenderGroup::UI);
    //============================
    if (Engine::FindObject((int)LayerGroup::Player, L"Player", NULL) == nullptr)
        Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", TestPlayer::Create({ 1.0f,1.0f,1.0f }));
    else
    {
        Engine::GameObject* pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL);
        pPlayer->GetComponent<Player>()->ResetPlayer({ 1.0f,1.0f,1.0f });
        pPlayer->SetActive(true);
    }
    UIinitialize();
    return false;
}
bool DefaultStageScene::UIinitialize()
{
    //컴포넌트(배경)
    Engine::GameObject* pHUDObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pHUDObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pHUDObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::BackGround);
    //타이머
    Engine::GameObject* pTimerObj = Engine::GameObject::Create();
    pTimerObj->AddComponent<TimerHUD>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pTimerObj); pTimerObj->SetRenderGroup((int)RenderGroup::UI);
    //게임오버 팝업
    Engine::GameObject* pGameOverObj = Engine::GameObject::Create();
    pGameOverObj->AddComponent<GameOverHUD>();
    pGameOverObj->AddComponent<GameOVerButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"GameOver", pGameOverObj); pGameOverObj->SetRenderGroup((int)RenderGroup::Fade); //팝업이라 더 높게..
    //게임클리어 팝업
    Engine::GameObject* pGameClearObj = Engine::GameObject::Create();
    pGameClearObj->AddComponent<GameClearHUD>();
    pGameClearObj->AddComponent<GameClearButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"GameClear", pGameClearObj); pGameClearObj->SetRenderGroup((int)RenderGroup::Fade);
    return false;
}

