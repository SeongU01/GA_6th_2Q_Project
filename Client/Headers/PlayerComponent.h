#pragma once
#include "Component.h"
#include "ICollisionNotify.h"
class PlayerComponent : public Engine::Component, public Engine::ICollisionNotify
{
	void Start() override;
	// ICollisionNotify��(��) ���� ��ӵ�
	void OnCollisionEnter(CollisionInfo& info) override;
	void OnCollision(CollisionInfo& info) override;
	void OnCollisionExit(CollisionInfo& info) override;

	// Component��(��) ���� ��ӵ�
	void Free() override;
};

