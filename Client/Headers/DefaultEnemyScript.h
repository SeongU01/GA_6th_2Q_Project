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
class AStar;
class DefaultEnemyScript:public Engine::MonoBehavior
{
	friend class DefaultEnemyState;
public:
	explicit DefaultEnemyScript(const wchar_t* name, const Vector3& startPos, const std::wstring& _targetName);
private:
	virtual ~DefaultEnemyScript() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	GridMovement* _movement = nullptr;
	AStar* _aStar = nullptr;
	HP* _pHP = nullptr;
	Engine::FiniteStateMachine* _pFSM = nullptr;
	Engine::Animation* _pAnimation = nullptr;
private:
	Vector3 _gridPosition = { 0.f,2.f,0.f };
	Vector3 _startPosition;
	Vector3 _targetPosition;
	Engine::GameObject* _pTargetObject = nullptr;
	std::wstring _targetObjectName;
	DefenseScript* _pDefense = nullptr;
};
