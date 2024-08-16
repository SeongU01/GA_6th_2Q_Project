#include "SelectCard.h"

// Component
#include "TextRenderer.h"
#include "Card.h"
#include "Button.h"
#include "CardSystem.h"

#include "Client_Define.h"

SelectCard::SelectCard()
	: MonoBehavior(L"SelectCard")
{
}

void SelectCard::Awake()
{

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
    /*_isOnSelectCard = true;
    _alpha = 0.f;

    _selectCardScene = Engine::GameObject::Create();
    _selectCardScene->SetRenderGroup((int)RenderGroup::Fade);

    Engine::TextRenderer* pTextRenderer = _selectCardScene->AddComponent<Engine::TextRenderer>(L"", 0xFFFFFF, 150.f, DWRITE_FONT_WEIGHT_BOLD);
    pTextRenderer->SetText(L"STAGE CLEAR!!");
    pTextRenderer->SetDrawRect((float)WINCX, 200.f);
    pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    pTextRenderer->SetOffset(Vector3(0.f, 50.f, 0.f));

    pTextRenderer = _selectCardScene->AddComponent<Engine::TextRenderer>(L"", 0xFFFFFF, 50.f, DWRITE_FONT_WEIGHT_BOLD);
    pTextRenderer->SetText(L"ȹ���� ī�带 �����ϼ���.");
    pTextRenderer->SetDrawRect((float)WINCX, 200.f);
    pTextRenderer->SetOffset(Vector3(0.f, 900.f, 0.f));
    pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

    Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", _selectCardScene);

    Engine::SpriteRenderer* pSpriteRenderer = _selectCardScene->GetComponent<Engine::SpriteRenderer>();
    pSpriteRenderer->SetOneSelfDraw(true, [=]()
        {
            pSpriteRenderer->DrawFillRect({ WINCX, WINCY }, 0x000000, _alpha);
        });    

    for (int i = 0; i < 3; i++)
    {
        Button* pButton = _selectCardScene->AddComponent<Button>();
        pButton->SetRange(pCards[i]->transform.position, { 540.f * 0.6f, 786.f * 0.6f });
        pButton->SetOnHover([=]() { pCards[i]->transform.scale = Vector3(0.66f, 0.66f, 0.f); });
        pButton->SetCancel([=]() { pCards[i]->transform.scale = Vector3(0.6f, 0.6f, 0.f); });
        pButton->SetOnPressed([=]()
            {
                CardSystem* pCardSystem = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr)->GetComponent<CardSystem>();
                pCardSystem->AddCard(CloneCard(pCards[i]->GetID()));
                pCardSystem->AddCard(CloneCard(pCards[i]->GetID()));
                pCards[i]->gameObject.SetActive(false);
                pCards[i]->_isSelectCard = false;

                for (int j = 0; j < 3; j++)
                {
                    if (i != j)
                        _cardIDs.push_back(pCards[j]->GetID());

                    pCards[j]->gameObject.SetDead();
                }

                _selectCardScene->SetDead();
                return;
            });
    }*/
}
