#pragma once
#include "Component.h"
#include "ICollisionNotify.h"

namespace Engine
{
	class Transform;
	class MonoBehavior abstract : public Component, public ICollisionNotify
	{
	protected:
		explicit MonoBehavior(const char* name);
		virtual ~MonoBehavior() = default;

	public:
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void FixedUpdate() {}
		virtual void Update(const float& deltaTime) = 0;
		virtual void LateUpdate(const float& deltaTime) = 0;

	public:
		// ICollisionNotify��(��) ���� ��ӵ�
		void OnCollisionEnter(CollisionInfo& info) override;
		void OnCollision(CollisionInfo& info) override;
		void OnCollisionExit(CollisionInfo& info) override;

	public:
		// Component��(��) ���� ��ӵ�
		void Free() override;
		
	};
}