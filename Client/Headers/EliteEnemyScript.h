#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Animation;
	class GameObject;
	class FiniteStateMachine;
}
class HP;
class GridMovement;
class DefenseScript;
class Player;
class AStar;
class Pannel;
class EliteEnemyScript :public Engine::MonoBehavior
{
	friend class EliteEnemyState;
public:
	explicit EliteEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName);
private:
	virtual ~EliteEnemyScript() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
public:
	virtual void OnCollisionEnter(Engine::CollisionInfo& info);
	virtual void OnCollision(Engine::CollisionInfo& info);
	virtual void OnCollisionExit(Engine::CollisionInfo& info);
private:
	GridMovement* _movement = nullptr;
	AStar* _aStar = nullptr;
	HP* _pHP = nullptr;
	Engine::FiniteStateMachine* _pFSM = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	Pannel* _pPannel = nullptr;
private:
	Vector3 _gridPosition = { 0.f,2.f,0.f };
	Vector3 _startPosition;
	Vector3 _targetPosition;
	Engine::GameObject* _pTargetObject = nullptr;
	std::wstring _targetObjectName;
	DefenseScript* _pDefense = nullptr;
	Player* _pPlayer = nullptr;
};


