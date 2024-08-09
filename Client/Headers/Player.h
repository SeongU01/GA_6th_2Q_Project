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
class Player : public Engine::MonoBehavior
{
public:
	explicit Player(const wchar_t* name, const Vector3& startPos);
private:
	virtual ~Player() = default;

public:
	Vector3 GetGridPosition() { return _gridPosition; }
	void ResetPlayer(const Vector3& startPos);

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
private:
	Vector3 _gridPosition = { 0.f,2.f,0.f };
	Vector3 _startPosition;
};

