#include "Card.h"
#include "CardSystem.h"

// Component
#include "TextRenderer.h"

#include "Client_Define.h"

Card::Card(const wchar_t* name, int costMana, float costTime, float delayBefore, float delayAfter, const wchar_t* textureTag, int index, CardType type, int targetType, int targetNum)
	: MonoBehavior(name), _costMana(costMana), _costTime(costTime), _delayBefore(delayBefore), _delayAfter(delayAfter)
{
	/*Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindTexture(Resource::FindTexture(textureTag));
	pSpriteRenderer->SetIndex(index);	*/
}

void Card::Awake()
{
}

void Card::Start()
{
}

void Card::Update(const float& deltaTime)
{
}

void Card::LateUpdate(const float& deltaTime)
{
}
