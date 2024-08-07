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
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	int GetID() const { return _cardData.ID; }
	float GetPriority() const { return _priority; }
	void SetHand();
	void SetOffset(const Vector3& offset);
	void SetPriority(float priority) { _priority = priority; }

	void Reset();

public:
	__declspec(property(get = GetID)) int ID;
	__declspec(property(get = GetPriority, put = SetPriority)) float priority;

private:
	CardData			_cardData{};
	std::wstring		_costMana;
	std::wstring		_costTime;
	Vector3				_offset;
	Engine::Collider*	_pCollider = nullptr;
	float				_priority = 0.f;
};

