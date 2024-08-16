#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class EventInvoker;
	class ShaderColor;
}

class HitColor : public Engine::MonoBehavior
{
public:
	explicit HitColor();
private:
	virtual ~HitColor() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void OnHitColorEffect(float duration);

private:
	Engine::EventInvoker*	_pEventInvoker = nullptr;
	Engine::ShaderColor*	_pShaderColor = nullptr;
	float					_hitColor = 0.f;
	float					_duration = 0.f;
	bool					_isOnHitColorEffect = false;
};

