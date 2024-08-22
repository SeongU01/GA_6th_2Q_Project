#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Collider;
	class GameObject;
	class EventInvoker;
}

enum class CardType;
enum class CardEffectType;
enum class CardAttribute;
class CardEffect;
class ToolTip;
class Card final : public Engine::MonoBehavior
{
	friend class CardManager;
	friend class CardSystem;
	friend class JobQueue;
public:
	struct CardData
	{
		std::wstring name;
		int actionID{};
		int iconID{};
		int variable[4]{};
		int targetNum[2]{};
		CardEffectType effectType[2]{};
		int additiveCharState[2]{};
		CardAttribute additiveCardState[2]{};
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
	struct CardAction
	{
		std::wstring animation;
		std::wstring effectTag;
		Vector3 position;
		Vector3 scale;
		float duration = 0.f;
		float delay = 0.f;
		float attackDelay = 0.f;
		bool isOneDraw = false;
		bool isFollow = false;
		bool isRotation = false;
	};
private:
	enum Type { Hand, Queue, End };
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
	float GetCostTime() { return _cardData.costTime; }
	int GetID() const { return _cardData.ID; }
	float GetPriority() const { return _priority; }
	bool GetHoldCard() const { return _isHoldMouse; }
	bool IsAddQueue() const { return _isAddQueue; }
	bool IsAddDrow();
	void SetHoldCard(bool isActive);
	void SetMouseHover(bool isHover);
	void SetTargetPosition(const Vector3& p0, const Vector3& p1);
	void SetFixPosition(const Vector3& position) { _fixPosition = position; }
	void ResetCardInfo();
	void Reset();
	void ActiveToolTips(bool isActive);
	void SetPlayerActives(bool _isActive);
	void SetSelectCardToolTipInfo();

public:
	void OnCollision(Engine::CollisionInfo& info) override;

private:
	bool AddJobQueue();
	void ActiveEffect();
	bool DrawCard();
	void ThrowCard();
	Vector3 SmoothStep(const XMVECTOR& v0, const XMVECTOR& v1, float t);
	void HandDeckSetting();
	void JobQueueSetting();
	void CreateEffect(const Card::CardAction& action, const Vector3& offset);

public:
	__declspec(property(get = GetID)) int ID;
	__declspec(property(get = GetPriority)) float priority;
	__declspec(property(get = GetHoldCard, put = SetHoldCard)) bool isHold;

private:
	void Free() override;

private:
	CardData							_cardData{};
	std::vector<CardAction>				_cardActions;
	std::wstring						_costMana;
	std::wstring						_costTime;
	std::vector<std::pair<int, int>>	_attackRange;
	Vector3								_offset;
	Vector3								_scale;
	Vector3								_targetScale[2];
	Vector3								_targetOffset[2];
	Vector3								_fixPosition;
	Vector3								_toGridPosition;
	Engine::Collider*					_pCollider = nullptr;
	Engine::GameObject*					_pPlayer = nullptr;
	Engine::EventInvoker*				_pEventInvoker = nullptr;
	ToolTip*							_pToolTip = nullptr;
	CardEffect*							_pCardEffect[2]{};
	D2D1_SIZE_F							_pixelSize[End]{};
	float								_priority = 0.f;
	float								_lerpTime = 0.f;
	bool								_isLerp = false;
	bool								_isThrow = false;
	bool								_isHoldMouse = false;
	bool								_isAddQueue = false;
	bool								_isAddDrow = false;
	bool								_isSelectCard = false;
};

