#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Rigidbody2D;
	class FiniteStateMachine;
}

class Player : public Engine::MonoBehavior
{
public:
	explicit Player(const char* name);
private:
	virtual ~Player() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	Engine::Rigidbody2D*		_pRigidbody = nullptr;
	Engine::FiniteStateMachine* _pFSM = nullptr;
};

