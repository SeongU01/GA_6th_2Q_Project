#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Collider;
	class GameObject;
}

enum class CardType;
enum class CardEffectType;
class Card final : public Engine::MonoBehavior
{
	friend class CardSystem;
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
	bool GetHoldCard() const { return _isHoldMouse; }
	void SetHoldCard(bool isActive);
	void SetMouseHover(bool isHover);

private:
	void SetHandDeckPosition(const Vector3& position) { _handDeckPosition = position; }
	void DrawCard();
	void ThrowCard();
	void Reset();
	bool ActiveEffect();

public:
	__declspec(property(get = GetID)) int ID;
	__declspec(property(get = GetPriority)) float priority;
	__declspec(property(get = GetHoldCard, put = SetHoldCard)) bool isHold;

private:
	Vector3 SmoothStep(const XMVECTOR& v0, const XMVECTOR& v1, float t);

private:
	CardData			_cardData{};
	std::wstring		_costMana;
	std::wstring		_costTime;
	Vector3				_offset;
	Vector3				_scale;
	Vector3				_targetScale[2];
	Vector3				_targetOffset[2];
	Vector3				_handDeckPosition;
	Engine::Collider*	_pCollider = nullptr;
	Engine::GameObject* _pPlayer = nullptr;
	D2D1_SIZE_F			_pixelSize{};
	float				_priority = 0.f;
	float				_lerpTime = 0.f;
	bool				_isLerp = false;
	bool				_isThrow = false;
	bool				_isHoldMouse = false;
};

