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
                Sound::StopSound((int)SoundGroup::Time);
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
    Sound::StopSound((int)SoundGroup::Voice);
    Sound::PlaySound("Voice_Sound_Voice_Zero_Over_Game", (int)SoundGroup::Voice, 0.8f, false);
    Sound::PlaySound("Effect_Sound_FX_Stage_Battle_Fail", (int)SoundGroup::SFX, 0.8f, false);
    _isRestart = true;
    _alpha = 0.f;
    _elapsed = 0.f;

    _pRestartGame = Engine::GameObject::Create();
    _pRestartGame->SetRenderGroup((int)RenderGroup::Top);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", _pRestartGame);

    Engine::SpriteRenderer* pSpriteRenderer = _pRestartGame->GetComponent<Engine::SpriteRenderer>();
    Engine::Texture* pTexture = Resource::FindTexture(L"UI_Text");

    pSpriteRenderer->SetOneSelfDraw(true, [=]()
        {
            pSpriteRenderer->DrawFillRect({ WINCX, WINCY }, 0x000000, _alpha);
        });

    _pEventInvoker->BindAction(1.f, [=]()
        {
            Engine::SpriteRenderer* pSpriteRenderer = _pRestartGame->AddComponent<Engine::SpriteRenderer>(L"");
            pSpriteRenderer->BindTexture(pTexture);
            pSpriteRenderer->SetIndex(2);
            pSpriteRenderer->SetDrawOffset(Vector3(WINCX >> 1, (WINCY >> 1) - 150.f, 0.f));
        });

    _pEventInvoker->BindAction(1.5f, [=]()
        {
            Engine::SpriteRenderer* pSpriteRenderer = _pRestartGame->AddComponent<Engine::SpriteRenderer>(L"");
            pSpriteRenderer->BindTexture(pTexture);
            pSpriteRenderer->SetIndex(3);
            pSpriteRenderer->SetDrawOffset(Vector3(WINCX >> 1, (WINCY >> 1) + 150.f, 0.f));
        });

    Time::SetSlowTime(0.f);
}
