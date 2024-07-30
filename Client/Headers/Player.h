#pragma once
#include "MonoBehavior.h"
#include "ICollisionNotify.h"

namespace Engine
{
	class Rigidbody2D;
}

class Player : public Engine::MonoBehavior, public Engine::ICollisionNotify
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

public:
	// ICollisionNotify을(를) 통해 상속됨
	void OnCollisionEnter(CollisionInfo& info) override;
	void OnCollision(CollisionInfo& info) override;
	void OnCollisionExit(CollisionInfo& info) override;

private:
	// Component을(를) 통해 상속됨
	void Free() override;	

private:
	Engine::Rigidbody2D* _pRigidbody = nullptr;
};

