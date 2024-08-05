#pragma once
#include "MonoBehavior.h"
#include "TextRenderer.h"
class TimerSystem :public Engine::MonoBehavior , public Engine::SingleTon<TimerSystem>
{
	friend class SingleTon;
public:
	explicit TimerSystem();
private:
	virtual ~TimerSystem() = default;
public:
	float GetRemainingTime() { return _maxTime-_curTime; }
	void SetTextComponent(Engine::TextRenderer* _comp) { _Text = _comp; }
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(const float& deltaTime) override;
	virtual void LateUpdate(const float& deltaTime) override;
private:
	Engine::TextRenderer* _Text = nullptr;
	float _curTime = 0.0f;
	float _maxTime=60.f;
	wchar_t _buffer[32];
};