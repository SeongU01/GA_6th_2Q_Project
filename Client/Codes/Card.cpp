#include "Card.h"
#include "CardSystem.h"

// Component
#include "TextRenderer.h"
#include "Collider.h"

#include "Client_Define.h"


Card::Card(const CardData& cardData)
	: MonoBehavior(cardData.name.c_str()), _cardData(cardData)
{
}

void Card::Awake()
{
	Engine::Texture* pTexture = Resource::FindTexture(L"Card");

	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindTexture(pTexture);
	pSpriteRenderer->SetIndex((int)_cardData.type);

	transform->position = Vector3(500.f, 500.f, 0.f);
	// transform->scale = Vector3(0.34f, 0.34f, 0.f);

	// 카드 이름
	Engine::TextRenderer* pTextRenderer = AddComponent<Engine::TextRenderer>(L"Title", D2D1::ColorF::White, 50.f, DWRITE_FONT_WEIGHT_BOLD);
	pTextRenderer->SetText(_cardData.name.c_str());
	pTextRenderer->SetDrawRect({ 0.f, 0.f, 450.f, 100.f });
	pTextRenderer->SetOffset(Vector3(-225.f, -50.f, 0.f));
	pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	// 카드 코스트
	pTextRenderer = AddComponent<Engine::TextRenderer>(L"CostTime", D2D1::ColorF::Black, 70.f, DWRITE_FONT_WEIGHT_BOLD);
	pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	pTextRenderer->SetOffset(Vector3(-280.f, -390.f, 0.f));
	pTextRenderer->SetDrawRect({ 0.f, 0.f, 200.f, 200.f });
	wchar_t buffer[16];

	int integer = (int)_cardData.costTime * 100;
	int hundredths = int(_cardData.costTime * 100);

	wsprintf(buffer, L"%d:%d", (int)_cardData.costTime, hundredths - integer);
	_costTime = buffer;
	pTextRenderer->SetText(_costTime.c_str());

	pTextRenderer = AddComponent<Engine::TextRenderer>(L"CostMana", 0x5555ff, 55.f, DWRITE_FONT_WEIGHT_BOLD);
	pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	pTextRenderer->SetOffset(Vector3(-245.f, -314.f, 0.f));
	pTextRenderer->SetDrawRect({ 0.f, 0.f, 200.f, 100.f });

	wsprintf(buffer, L"[%d]", _cardData.costMana);
	_costMana = buffer;
	pTextRenderer->SetText(_costMana.c_str());

	_pCollider = AddComponent<Engine::Collider>(L"Card");
	
	D2D1_SIZE_F pixelSize = pTexture->GetImage(0)->GetSize();
	_pCollider->SetScale({ pixelSize.width, pixelSize.height, 0.f });
	_pCollider->SetActive(false);

	gameObject->_isDrawCollider = true;
}

void Card::Start()
{
}

void Card::Update(const float& deltaTime)
{	
}

void Card::LateUpdate(const float& deltaTime)
{
	transform->position += _offset;
}

void Card::SetHand()
{
	transform->scale = Vector3(0.34f, 0.34f, 0.f);
	_pCollider->SetActive(true);
}

void Card::Reset()
{
	transform->scale = Vector3(1.f, 1.f, 0.f);
	gameObject->SetActive(false);
	_pCollider->SetActive(false);
}

void Card::SetOffset(const Vector3& offset)
{
	_offset = offset;
}
