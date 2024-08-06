#pragma once 
#include "MonoBehavior.h"
namespace Engine
{
	class Animation;
	class FiniteStateMachine;
}
class GridMovement;

class Enemy : public Engine::MonoBehavior
{
public:
	explicit Enemy(const wchar_t* name);
private:
	virtual ~Enemy() = default;

public:
	void SetGridPosition(const Vector3& position) { _gridPosition = position; }
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	GridMovement* _movement = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	Engine::FiniteStateMachine* _pFSM = nullptr;
private:
	Vector3 _gridPosition = { 0.f,0.f,0.f };

};