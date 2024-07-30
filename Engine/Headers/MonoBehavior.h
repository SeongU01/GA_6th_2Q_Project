#pragma once
#include "Component.h"

namespace Engine
{
	class Transform;
	class MonoBehavior abstract : public Component
	{
	protected:
		explicit MonoBehavior(const char* name);
		virtual ~MonoBehavior() = default;

	public:
		virtual void Initialize() final;
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void FixedUpdate() {}
		virtual void Update(const float& deltaTime) = 0;
		virtual void LateUpdate(const float& deltaTime) = 0;

	public:
		// Component을(를) 통해 상속됨
		void Free() override;

	protected:
		Transform* _pTransform = nullptr;
	};
}