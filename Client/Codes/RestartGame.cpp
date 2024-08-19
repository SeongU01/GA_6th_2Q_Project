#include "RestartGame.h"

// Component
#include "EventInvoker.h"
#include "TextRenderer.h"

#include "Client_Define.h"

RestartGame::RestartGame()
	: MonoBehavior(L"RestartGame")
{
}

void RestartGame::Awake()
{
}

void RestartGame::Start()
{
}

void RestartGame::Update(const float& deltaTime)
{
}

void RestartGame::LateUpdate(const float& deltaTime)
{
}

void RestartGame::GameOver()
{
    _alpha = 0.f;

    _pRestartGame = Engine::GameObject::Create();
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

    _pEventInvoker->BindAction(2.5f, [this]()
        {
            Engine::TextRenderer* pTextRenderer = _pRestartGame->AddComponent<Engine::TextRenderer>(L"", 0xFFFFFF, 50.f, DWRITE_FONT_WEIGHT_BOLD);
            pTextRenderer->SetText(L"Press Space to Retry");
            pTextRenderer->SetDrawRect((float)WINCX, 200.f);
            pTextRenderer->SetOffset(Vector3(0.f, 900.f, 0.f));
            pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        });
}
