#pragma once
#include "DefaultEnemyState.h"

class DefaultEnemyIdle:public DefaultEnemyState
{
private:
	explicit DefaultEnemyIdle() = default;
	virtual ~DefaultEnemyIdle() = default;
public:
		// DefaultEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;

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
};

