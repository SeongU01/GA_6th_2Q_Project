#include "DefaultStageScene.h"
#include "Client_Define.h"

// Script
#include "Mouse.h"
#include "DeckSystem.h"
#include "TimerSystem.h"

// UI
#include "TimerHUD.h"
#include "GameOverHUD.h"
#include "GameOverButtons.h"
#include "GameClearHUD.h"
#include "GameClearButtons.h"
#include "HPHUD.h"
#include "TopHUD.h"
#include "MPHUD.h"

// Object
#include "CollisionManager.h"
#include "Zero.h"
#include "Obstacle.h"
#include "Player.h"
#include "Defense.h"


void DefaultStageScene::Free()
{
    SafeRelease(_pCollisionManager);
}

void DefaultStageScene::MakeObject(const ObjectArrangeInfo& objInfo)
{
  for (auto obj : objInfo.objectInfos)
  {
    //ID���� object �׸��忡 ����
    switch (obj.objectID)
    {
    case 0:
      //TODO:��� ��ǥ(������) object����� �߰��ϱ�
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Defense",
        Defense::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x , obj.objectPosition.y, 0.f)),
          Vector3(0.f, -60.f, 0.f), obj.objectTag,
          L"Defense_Generator")
      );
      break;
    case 1:
      //TODO:��� ��ǥ(��������) object����� �߰��ϱ�
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
        Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>()->ResetPlayer(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f));
      break;
    }
  }
}

int DefaultStageScene::Update(const float& deltaTime)
{
    //�׽�Ʈ�� �ڵ�(���ӿ���, Ŭ���� �˾� üũ
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
    _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"), 
                                       Engine::FindObjectList((int)LayerGroup::Object, L"Card"));

    _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"),
                                       Engine::FindObjectList((int)LayerGroup::Enemy, L"Monster"));

    _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::Player, L"Player"),
                                       Engine::FindObjectList((int)LayerGroup::Enemy, L"Monster"));

    return 0;
}

bool DefaultStageScene::Initialize()
{
    _pCollisionManager = Engine::CollisionManager::Create();
    
    Engine::GameObject* pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL);

    if (nullptr == pPlayer)
    {
        pPlayer = Zero::Create({ 3.0f,1.0f,1.0f });
        Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", pPlayer);

        // TOPHUD
        Engine::GameObject* pHPHUDObj = Engine::GameObject::Create();
        pHPHUDObj->SetDontDestroyObject(true);
        Engine::AddObjectInLayer((int)LayerGroup::UI, L"PlayerTopHP", pHPHUDObj);

        pHPHUDObj->AddComponent<TopHUD>(pPlayer->GetComponent<Player>()->GetPlayerHPComponent(), 1);
        pHPHUDObj->SetRenderGroup((int)RenderGroup::UI);
    }
    else
    {        
        pPlayer->GetComponent<Player>()->ResetPlayer({ 4.0f, 4.0f, 1.0f });
        pPlayer->SetActive(true);
        pPlayer->GetComponent<HPHUD>()->SetActives(true);
    }

    UIinitialize();

    // Mouse
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetName(L"Mouse");
    pObject->SetRenderGroup((int)RenderGroup::UI);
    pObject->AddComponent<Mouse>(L"Mouse");
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Mouse", pObject);

    return true;
}

bool DefaultStageScene::UIinitialize()
{
    // �� �ý���
    Engine::GameObject* pGameObject = Engine::GameObject::Create();
    pGameObject->AddComponent<DeckSystem>();
    pGameObject->SetRenderGroup((int)RenderGroup::UI);
    pGameObject->transform.position = Vector3(1725.f, 985.f, 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pGameObject);

    // ������Ʈ(���)
    Engine::GameObject* pHUDObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pHUDObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pHUDObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::BackGround);

    // Ÿ�̸�
    Engine::GameObject* pTimerObj = Engine::GameObject::Create();
    pTimerObj->AddComponent<TimerHUD>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"TimerObj", pTimerObj); pTimerObj->SetRenderGroup((int)RenderGroup::UI);

    // ���� ��
    Engine::GameObject* pMPHUDDObj = Engine::GameObject::Create();
    pMPHUDDObj->transform.SetPosition(Vector3(250, 920.0f, 0));
    pMPHUDDObj->AddComponent<MPHUD>(Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<Player>()->GetPlayerMPComponent(), 0);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"MPHUD", pMPHUDDObj); pMPHUDDObj->SetRenderGroup((int)RenderGroup::UI);

    // ���ӿ��� �˾�
    Engine::GameObject* pGameOverObj = Engine::GameObject::Create();
    pGameOverObj->AddComponent<GameOverHUD>();
    pGameOverObj->AddComponent<GameOVerButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"GameOver", pGameOverObj); pGameOverObj->SetRenderGroup((int)RenderGroup::Top); //�˾��̶� �� ����..

    // ����Ŭ���� �˾�
    Engine::GameObject* pGameClearObj = Engine::GameObject::Create();
    pGameClearObj->AddComponent<GameClearHUD>();
    pGameClearObj->AddComponent<GameClearButtons>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"GameClear", pGameClearObj); pGameClearObj->SetRenderGroup((int)RenderGroup::Top);    

    return true;
}

