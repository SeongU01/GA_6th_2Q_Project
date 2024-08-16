#include "HitColor.h"

// Component
#include "EventInvoker.h"

HitColor::HitColor()
	: MonoBehavior(L"HitColor")
{
}

void HitColor::Awake()
{
	_pEventInvoker = AddComponent<Engine::EventInvoker>(L"EventInvoker");
	_pShaderColor = GetComponent<Engine::SpriteRenderer>(L"SpriteRenderer")->GetShader<Engine::ShaderColor>();
}

void HitColor::Start()
{
}

void HitColor::Update(const float& deltaTime)
{
	if (_isOnHitColorEffect)
	{
		_hitColor -= deltaTime / _duration;
		_pShaderColor->SetUseColor(_hitColor, _hitColor, _hitColor);
	}
}

void HitColor::LateUpdate(const float& deltaTime)
{
}

void HitColor::OnHitColorEffect(float duration)
{
	_isOnHitColorEffect = true;
	_hitColor = 1.f;
	_duration = duration;

	_pEventInvoker->BindAction(duration, [this]()
		{
			_isOnHitColorEffect = false; 
			_hitColor = 0.f;
			_pShaderColor->SetUseColor(_hitColor, _hitColor, _hitColor);
		});
}
