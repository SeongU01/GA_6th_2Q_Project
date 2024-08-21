#include "SelectCard.h"

// Component
#include "TextRenderer.h"
#include "Card.h"
#include "Button.h"
#include "CardSystem.h"
#include "EventInvoker.h"

#include "EventManager.h"
#include "CardManager.h"
#include "Client_Define.h"

SelectCard::SelectCard()
	: MonoBehavior(L"SelectCard")
{
}

void SelectCard::Awake()
{
    _pEventInvoker = AddComponent<Engine::EventInvoker>(L"EventInvoker");
    _pEventInvoker->SetUseGlobalDeltaTime(true);
}

void SelectCard::Start()
{
}

void SelectCard::Update(const float& deltaTime)
{
    if (_isOnSelectCard)
    {
        if (0.8f >= _alpha)
            _alpha += Time::GetGlobalDeltaTime();        
    }
}

void SelectCard::LateUpdate(const float& deltaTime)
{
}

void SelectCard::OnSelectCard(Card* pCards[3])
{
    Sound::StopSound((int)SoundGroup::Voice);
    Sound::PlaySound("Voice_Sound_Voice_Zero_Clear_Game", (int)SoundGroup::Voice, 0.8f, false);
    Card* cards[3];
    for (int i = 2; i >= 0; i--)
        cards[i] = pCards[2 - i];

    _isOnSelectCard = true;
    _alpha = 0.f;

    _selectCardScene = Engine::GameObject::Create();
    _selectCardScene->SetRenderGroup((int)RenderGroup::Fade);
    _selectCardScene->transform.position = Vector3(0.f, 0.f, -4.f);
    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", _selectCardScene);

    Engine::SpriteRenderer* pSpriteRenderer = _selectCardScene->GetComponent<Engine::SpriteRenderer>();
    Engine::Texture* pTexture = Resource::FindTexture(L"UI_Text");

    pSpriteRenderer->SetOneSelfDraw(true, [=]()
        {
            pSpriteRenderer->DrawFillRect({ WINCX, WINCY }, 0x000000, _alpha);
        });

    _pEventInvoker->BindAction(1.f, [=]()
        {
            Engine::SpriteRenderer* pSpriteRenderer = _selectCardScene->AddComponent<Engine::SpriteRenderer>(L"");
            pSpriteRenderer->BindTexture(pTexture);
            pSpriteRenderer->SetDrawOffset(Vector3(WINCX >> 1, 150.f, 0.f));
        });

    for (int i = 0; i < 3; i++)
    {        
        _pEventInvoker->BindAction(1.2f, [=]()
            {
                Sound::PlaySound("Card_Sound_Card_ClearSlide", (int)SoundGroup::Card, 0.8f, false);
                Sound::PlaySound("Effect_Sound_FX_Stage_Battle_Clear", (int)SoundGroup::SFX, 0.8f, false);
                cards[i]->gameObject.SetActive(true);
                cards[i]->SetTargetPosition(Vector3(0.f, 1000.f, 0.f), Vector3(0.f, 0.f, 0.f));
                Button* pButton = _selectCardScene->AddComponent<Button>();
                pButton->SetRange(cards[i]->transform.position, { 540.f * 0.6f, 786.f * 0.6f });
                pButton->SetOnHover([=]() { 
                    cards[i]->ActiveToolTips(true);
                    cards[i]->transform.scale = Vector3(0.66f, 0.66f, 0.f); 
                    });
                pButton->SetCancel([=]() {             
                    cards[i]->ActiveToolTips(false);
                    cards[i]->transform.scale = Vector3(0.6f, 0.6f, 0.f);
                    });
                pButton->SetOnPressed([=]()
                    {
                        Sound::PlaySound("Card_Sound_Card_ClearSelect", (int)SoundGroup::Card, 0.8f, false);
                        CardSystem* pCardSystem = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<CardSystem>();
                        CardManager* pCardManager = CardManager::GetInstance();
                        pCardSystem->AddCard(pCardManager->CloneCard(cards[i]->GetID()));
                        pCardSystem->AddCard(pCardManager->CloneCard(cards[i]->GetID()));
                        cards[i]->gameObject.SetActive(false);

                        for (int j = 0; j < 3; j++)
                        {
                            if (i != j)
                                pCardManager->AddCardID(cards[j]->GetID());

                            cards[j]->ActiveToolTips(false);
                            cards[j]->gameObject.SetDead();
                        }

                        _selectCardScene->SetDead();
                        EventManager::GetInstance()->SetNextStage(true);
                        return;
                    });
            });
    }

    _pEventInvoker->BindAction(1.8f, [=]()
        {
            Engine::SpriteRenderer* pSpriteRenderer = _selectCardScene->AddComponent<Engine::SpriteRenderer>(L"");
            pSpriteRenderer->BindTexture(pTexture);
            pSpriteRenderer->SetIndex(1);
            pSpriteRenderer->SetDrawOffset(Vector3(WINCX >> 1, 900.f, 0.f));
        });    
}
