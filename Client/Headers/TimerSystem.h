#pragma once
#include "MonoBehavior.h"
#include "TextRenderer.h"
#include "UI.h"

class TimerSystem :public Engine::MonoBehavior
{
public:
	explicit TimerSystem();
private:
	virtual ~TimerSystem() = default;

public:
	float GetRemainingTime() { return _maxTime-_curTime; }
	float UseTime(float time) { return _curTime += time; }
	float AddPlayTime(float time) { _playTime += time; } //스킬이 진행될 시간(카드의 추가 및 삭제에 따른 변경.)

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(const float& deltaTime) override;
	virtual void LateUpdate(const float& deltaTime) override;

private:
	float _playTime = 0.0f;
	float _slowTime = 0.0f;
	float _curTime = 0.0f;
	float _maxTime=60.f;
	wchar_t _buffer[32];
};