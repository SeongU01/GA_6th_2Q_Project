#pragma once
#include "MonoBehavior.h"
namespace Engine
{
	class Animation;
	class FiniteStateMachine;
}

class HP;
class PlayerMP;
class AdditiveState;
class GridMovement;
class CardSystem;
class CombatEvent;
class TimerSystem;
class AttackCollider;
class Player : public Engine::MonoBehavior
{
public:
	explicit Player(const wchar_t* name, const Vector3& startPos);
private:
	virtual ~Player() = default;

public:
	const Vector3& GetGridPosition() const { return _gridPosition; }
	const Vector3& GetNextGridPosition() const { return _nextGridPosition; }
	void SetGridPostion(const Vector3& position);
	void SetNextGridPosition(const Vector3& position);
	void ResetPlayer(const Vector3& startPos);
	HP* GetPlayerHPComponent() { return _pHP; }
	PlayerMP* GetPlayerMPComponent() { return _pMP; }
	AttackCollider* GetPlayerAttackComponent() { return _pAttackCollider; }

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void OnCollisionEnter(Engine::CollisionInfo& info) override;
	void OnCollisionExit(Engine::CollisionInfo& info) override;

private:
	void DefaultMove(const float& deltaTime);

private:
	GridMovement* _movement = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	Engine::FiniteStateMachine* _pFSM = nullptr;

	AdditiveState* _pAdditiveState = nullptr;
	HP* _pHP = nullptr;
	PlayerMP* _pMP = nullptr;
	CardSystem* _pCardSystem = nullptr;
	CombatEvent* _pCombatEvent = nullptr;
	TimerSystem* _pTimerSystem = nullptr;
	AttackCollider* _pAttackCollider = nullptr;

private:
	std::vector<Engine::Collider*> _attackColliders;
	Vector3 _gridPosition = { 0.f, 2.f, 0.f };
	Vector3 _nextGridPosition;
	Vector3 _startPosition;
};

