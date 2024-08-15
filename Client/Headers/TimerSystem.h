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
	void AddSkillTime(float time) { _skillValue += time; }
	float GetSkillTime() { return _skillValue; }
	float GetMaxTime() { return _maxTime; }
	float GetisSlow() { return _slowTime == 0.0f; }
	float UseTime(float time) { return _curTime += time; }
	float AddPlayTime(float time) { _playTime += time; } //스킬이 진행될 시간(카드의 추가 및 삭제에 따른 변경.)
	void ResetTime(){ _playTime = 0.0f; _slowTime = 0.0f; _curTime = 0.0f;  _maxTime = 60.f;}
	bool IsStopTime() const { return _isStopTime; }

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(const float& deltaTime) override;
	virtual void LateUpdate(const float& deltaTime) override;

private:
	wchar_t _buffer[32];
	float _skillValue = 0.f; //스킬소모 타임
	float _playTime = 0.0f;
	float _slowTime = 0.0f;
	float _curTime = 0.0f;
	float _maxTime=60.f;
	bool _isNotice = false;
	bool _isStopTime = false;
};