#pragma once
#include "MonoBehavior.h"

class Card;
class AdditiveState;
class CombatEvent : public Engine::MonoBehavior
{
public:
	explicit CombatEvent();
private:
	virtual ~CombatEvent() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void ActiveCard(Card* pCard);
};

