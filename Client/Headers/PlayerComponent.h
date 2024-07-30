#pragma once
#include "Component.h"
#include "ICollisionNotify.h"
class PlayerComponent : public Engine::Component, public Engine::ICollisionNotify
{
	void Start() override;
	// ICollisionNotify을(를) 통해 상속됨
	void OnCollisionEnter(CollisionInfo& info) override;
	void OnCollision(CollisionInfo& info) override;
	void OnCollisionExit(CollisionInfo& info) override;

	// Component을(를) 통해 상속됨
	void Free() override;
};

