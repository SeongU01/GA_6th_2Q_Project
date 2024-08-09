#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Collider;
}

enum class CardType;
enum class CardEffectType;
class Card final : public Engine::MonoBehavior
{
public:
	struct CardData
	{
		std::wstring name{};
		int iconID{};
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
	float GetPriority() const { return _priority; }
	void SetHand();
	void SetHover(bool isHover);
	void ThrowCard();
	void Reset();

public:
	__declspec(property(get = GetID)) int ID;
	__declspec(property(get = GetPriority)) float priority;

private:
	CardData			_cardData{};
	std::wstring		_costMana;
	std::wstring		_costTime;
	Vector3				_offset;
	Vector3				_scale;
	Vector3				_targetScale[2];
	Vector3				_targetOffset[2];
	Engine::Collider*	_pCollider = nullptr;
	D2D1_SIZE_F			_pixelSize{};
	float				_priority = 0.f;
	float				_lerpTime = 0.f;
	bool				_isLerp = false;
};

