#pragma once
#include "MonoBehavior.h"
#include "TextRenderer.h"
#include "UI.h"
//½Ì±ÛÅæ¾ø¾Ö±â..

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
	void SetHeartsUIs(std::vector<UI*> _uis) { _RemainingUI= _uis; }
public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(const float& deltaTime) override;
	virtual void LateUpdate(const float& deltaTime) override;
private:
	Engine::TextRenderer* _Text = nullptr;
	std::vector<UI*> _RemainingUI;
	float _slowTime = 0.0f;
	float _curTime = 0.0f;
	float _maxTime=60.f;
	wchar_t _buffer[32];
};