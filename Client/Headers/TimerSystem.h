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
	float AddPlayTime(float time) { _playTime += time; } //��ų�� ����� �ð�(ī���� �߰� �� ������ ���� ����.)

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