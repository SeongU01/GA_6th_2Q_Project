#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class EventInvoker;
}

class Card;
class SelectCard : public Engine::MonoBehavior
{
public:
	explicit SelectCard();
private:
	virtual ~SelectCard() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void OnSelectCard(Card* pCards[3]);

private:
	Engine::GameObject*		_selectCardScene = nullptr;
	Engine::EventInvoker*	_pEventInvoker = nullptr;
	float					_alpha = 0.f;
	bool					_isOnSelectCard = false;
};

