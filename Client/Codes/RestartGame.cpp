#include "RestartGame.h"

// Component
#include "EventInvoker.h"
#include "TextRenderer.h"
#include "HP.h"

// Scene
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "Stage3Scene.h"
#include "Stage4Scene.h"

#include "EventManager.h"
#include "Client_Define.h"

RestartGame::RestartGame()
	: MonoBehavior(L"RestartGame")
{
}

void RestartGame::Awake()
{
    _pEventInvoker = AddComponent<Engine::EventInvoker>(L"EventInvoker");
    _pEventInvoker->SetUseGlobalDeltaTime(true);
}

void RestartGame::Start()
{
}

void RestartGame::Update(const float& deltaTime)
{
    if (_isRestart)
    {
        float delta = Time::GetGlobalDeltaTime();

        if (0.8f >= _alpha)
            _alpha += delta;

        _elapsed += delta;

        if (1.5f <= _elapsed)
        {
            if (Input::IsKeyDown(DIK_SPACE))
            {
                switch (_stage)
                {
                case Stage1:
                    Engine::ChangeScene(Stage1Scene::Create());
                    break;
                case Stage2:
                    Engine::ChangeScene(Stage2Scene::Create());
                    break;
                case Stage3:
                    Engine::ChangeScene(Stage3Scene::Create());
                    break;
                case Stage4:
                    Engine::ChangeScene(Stage4Scene::Create());
                    break;
                }

                _isRestart = false;
                _pRestartGame = nullptr;

                Engine::GameObject* pPlayer = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr);
                pPlayer->GetComponent<HP>()->hp = 5;

                EventManager::GetInstance()->SetPlayerDeath(false);
                Time::SetSlowTime(1.f);
            }
        }
    }
}

void RestartGame::LateUpdate(const float& deltaTime)
{    
}

void RestartGame::GameOver()
{
    _isRestart = true;
    _alpha = 0.f;

    _pRestartGame = Engine::GameObject::Create();
    _pRestartGame->SetRenderGroup((int)RenderGroup::Top);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", _pRestartGame);

    Engine::SpriteRenderer* pSpriteRenderer = _pRestartGame->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->SetOneSelfDraw(true, [=]()
        {
            pSpriteRenderer->DrawFillRect({ WINCX, WINCY }, 0x000000, _alpha);
        });

    _pEventInvoker->BindAction(1.f, [this]()
        {
            Engine::TextRenderer* pTextRenderer = _pRestartGame->AddComponent<Engine::TextRenderer>(L"", 0xFFFFFF, 150.f, DWRITE_FONT_WEIGHT_BOLD);
            pTextRenderer->SetText(L"Game Over");
            pTextRenderer->SetDrawRect((float)WINCX, 200.f);
            pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            pTextRenderer->SetOffset(Vector3(0.f, 50.f, 0.f));
        });

    _pEventInvoker->BindAction(1.5f, [this]()
        {
            Engine::TextRenderer* pTextRenderer = _pRestartGame->AddComponent<Engine::TextRenderer>(L"", 0xFFFFFF, 50.f, DWRITE_FONT_WEIGHT_BOLD);
            pTextRenderer->SetText(L"Press Space to Retry");
            pTextRenderer->SetDrawRect((float)WINCX, 200.f);
            pTextRenderer->SetOffset(Vector3(0.f, 900.f, 0.f));
            pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        });

    Time::SetSlowTime(0.f);
}
