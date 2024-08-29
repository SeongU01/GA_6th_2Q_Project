#include "DefaultStageScene.h"
#include "TitleScene.h"
#include "Client_Define.h"

// Script
#include "Mouse.h"
#include "DeckSystem.h"
#include "TimerSystem.h"
#include "CardSystem.h"
#include "GridEffect.h"
#include "HP.h"

// UI
#include "TimerHUD.h"
#include "HPHUD.h"
#include "TopHUD.h"
#include "MPHUD.h"
#include "Fade.h"

// Object
#include "Zero.h"
#include "Obstacle.h"
#include "Player.h"
#include "Defense.h"

#include "CardManager.h"
#include "EventManager.h"
#include "CollisionManager.h"

void DefaultStageScene::Free()
{
    SafeRelease(_pCollisionManager);
}

void DefaultStageScene::MakeObject(const ObjectArrangeInfo& objInfo)
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
          L"Defense_Generator",2)
      );
      break;
    case 1:
      //TODO:방어 목표(방위본부) object만들면 추가하기
      Engine::AddObjectInLayer((int)LayerGroup::Object, L"Defense",
        Defense::Create(
          std::pair(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f), Vector3(obj.objectPosition.x + 1.f, obj.objectPosition.y, 0.f)),
          Vector3(0.f, -80.f, 0.f), obj.objectTag,
          L"Defense_Command",3)
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
        Engine::GameObject* pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL);
        pPlayer->GetComponent<Player>()->ResetPlayer(Vector3(obj.objectPosition.x, obj.objectPosition.y, 0.f));
        pPlayer->GetComponent<CardSystem>()->StartGame();
      break;
    }
  }
}

void DefaultStageScene::FadeIn()
{
    //페이드 인.
    Fade::FadeInfo info;
    info.option = Fade::Fade_Option::Fade_In;
    info.color = 0xFF000000;
    info.duration = 1.0f;
    info.life = 1.0f;
    Engine::GameObject* pFadeObj = Engine::GameObject::Create();
    Fade* _pFade = pFadeObj->AddComponent<Fade>(info);

    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Fade", pFadeObj); pFadeObj->SetRenderGroup((int)RenderGroup::Fade);
}

int DefaultStageScene::Update(const float& deltaTime)
{


    auto objectList = Engine::FindObjectList((int)LayerGroup::Object, L"Defense");

    if (!objectList->empty())
    {
        size_t size = objectList->size();
        size_t count = 0;
        for (auto& object : *objectList)
        {
            HP* pHP = object->GetComponent<HP>();

            if (pHP->IsZeroHP())
                count++;
        }
        if (count == 1 && !_isRemainTower1)
        {
            Sound::StopSound((int)SoundGroup::Voice);
            Sound::PlaySound("Voice_Sound_Voice_Operator_Tower_1", (int)SoundGroup::Voice, 0.8f, false);
            _isRemainTower1 = true;
        }
        if (count == size)
            Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<HP>()->hp = 0;
    }

    return 0;
}

int DefaultStageScene::LateUpdate(const float& deltaTime)
{
    EventManager* pEventManager = EventManager::GetInstance();

    if (!pEventManager->IsPlayerDeath())
    {
        if (!pEventManager->IsStopGame())
        {
            _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"),
                Engine::FindObjectList((int)LayerGroup::Object, L"Card"));

            _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"),
                Engine::FindObjectList((int)LayerGroup::Enemy, L"Monster"));

            _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::Player, L"Player"),
                Engine::FindObjectList((int)LayerGroup::Enemy, L"Monster"));

            _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"), //방어건물
                Engine::FindObjectList((int)LayerGroup::Object, L"Defense"));

            _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"), //장애물
                Engine::FindObjectList((int)LayerGroup::Object, L"Buliding"));

            _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::UI, L"Mouse"), //산
                Engine::FindObjectList((int)LayerGroup::Object, L"Mountain"));

            _pCollisionManager->CheckCollision(Engine::FindObjectList((int)LayerGroup::Enemy, L"Monster"), //산
                Engine::FindObjectList((int)LayerGroup::Object, L"Defense"));
        }
        else
        {
            if (Stage::Stage4 == _currentStage)
            {
                pEventManager->SetNextStage(true);
            }
            else if (!_isSelectCard)
            {
                CardManager::GetInstance()->StartSelectCardScene();
                _isSelectCard = true;
            }
        }
    }

    if (pEventManager->IsNextStage())
    {
        for (int i = 0; i < (int)SoundGroup::End; i++)
        {
            Sound::StopSound(i);
        }
        pEventManager->SetNextStage(false);
        pEventManager->SetStopGame(false);
        Time::SetSlowTime(1.f);
        Engine::ChangeScene(_pScene);
    }

    /*if (Input::IsKeyDown(DIK_RBRACKET))
    {
        if (_pScene) Engine::ChangeScene(_pScene);
    }

    if (Input::IsKeyDown(DIK_LBRACKET))
    {
        Engine::RemoveAll();
        Engine::ChangeScene(TitleScene::Create());
    }*/

    return 0;
}

bool DefaultStageScene::Initialize()
{
    _pCollisionManager = Engine::CollisionManager::Create();    

    Engine::GameObject* pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL);

    if (nullptr == pPlayer)
    {
        pPlayer = Zero::Create({ 3.0f, 1.0f, 1.0f });
        Engine::AddObjectInLayer((int)LayerGroup::Player, L"Player", pPlayer);
    }
    else
    {        
        /*pPlayer->GetComponent<Player>()->ResetPlayer({ 1.0f, 1.0f, 1.0f });
        pPlayer->SetActive(true);
        pPlayer->GetComponent<HPHUD>()->SetActives(true);*/
    }

    UIinitialize();

    // Mouse
    Engine::GameObject* pObject = Engine::GameObject::Create();
    pObject->SetNotAffectCamera(true);
    pObject->SetName(L"Mouse");
    pObject->SetRenderGroup((int)RenderGroup::UI);
    pObject->AddComponent<Mouse>(L"Mouse");
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"Mouse", pObject);
    FadeIn();
    return true;
}

bool DefaultStageScene::UIinitialize()
{
    // 덱 시스템
    Engine::GameObject* pGameObject = Engine::GameObject::Create();
    pGameObject->SetNotAffectCamera(true);
    pGameObject->AddComponent<DeckSystem>();
    pGameObject->SetRenderGroup((int)RenderGroup::UI);
    pGameObject->transform.position = Vector3(1725.f, 985.f, 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pGameObject);

    // 컴포넌트(배경)
    Engine::GameObject* pHUDObj = Engine::GameObject::Create();
    Engine::SpriteRenderer* pSpriteRenderer = pHUDObj->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->BindTexture(Resource::FindTexture(L"BackGround"));
    pSpriteRenderer->SetIndex(0);
    pHUDObj->transform.position = Vector3(float(WINCX >> 1), float(WINCY >> 1), 0.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pHUDObj); pHUDObj->SetRenderGroup((int)RenderGroup::BackGround);

    // 타이머
    Engine::GameObject* pTimerObj = Engine::GameObject::Create();
    pTimerObj->AddComponent<TimerHUD>();
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"TimerObj", pTimerObj); pTimerObj->SetRenderGroup((int)RenderGroup::UI);

    return true;
}

