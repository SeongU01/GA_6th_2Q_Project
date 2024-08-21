#pragma once
#include "RangeEnemyState.h"

class RangeEnemyIdle :public RangeEnemyState
{
private:
	explicit RangeEnemyIdle() = default;
	virtual ~RangeEnemyIdle() = default;
public:
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;

	virtual void ShowInfo();
	virtual void CloseInfo();
private:
	RangeEnemy::FSM SelectNextBehave();
private:
	bool CheckTargetRange(int x, int y);

public:
	static RangeEnemyIdle* Create(RangeEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	RangeEnemy::FSM _nextState = RangeEnemy::FSM::None;

	float _alpha = 0.f;
	bool _isFandIn = false;
};

