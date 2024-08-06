#pragma once
#include "MonoBehavior.h"

enum class CardType;
enum class CardEffectType;
class Card final : public Engine::MonoBehavior
{
public:
	struct CardData
	{
		std::wstring name{};
		std::wstring textureTag{};
		int variable[4]{};
		int targetTypeID[2]{};
		int targetNum[2]{};
		CardEffectType effectType[2]{};
		int additiveCharState[2]{};
		int additiveCardState[2]{};
		int charStateNum[2]{};
		int ID{};
		int costMana{};
		float costTime{};
		float delayBefore{};
		float delayAfter{};
		CardType type{};
		int effectRelation{};
		int textID{};
	};
public:
	explicit Card(const CardData& cardData);
private:
	virtual ~Card() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	int GetID() const { return _cardData.ID; }
public:
	__declspec(property(get = GetID)) int ID;

private:
	CardData		_cardData{};
	std::wstring	_costMana;
	std::wstring	_costTime;
};

