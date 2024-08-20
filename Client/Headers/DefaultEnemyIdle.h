#pragma once
#include "DefaultEnemyState.h"

class DefaultEnemyIdle:public DefaultEnemyState
{
private:
	explicit DefaultEnemyIdle() = default;
	virtual ~DefaultEnemyIdle() = default;
public:
		// DefaultEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;

public:
	virtual void ShowInfo();
	virtual void CloseInfo();

private:
	DefaultEnemy::FSM SelectNextBehave();
private:
	bool CheckAttackRange(int x, int y);

public:
	static DefaultEnemyIdle* Create(DefaultEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	DefaultEnemy::FSM _nextState=DefaultEnemy::FSM::None;
	bool _checkState = false;
	int _chargeStack = 0;
	float _alpha = 0.f;
	bool _isFandIn = false;
};

