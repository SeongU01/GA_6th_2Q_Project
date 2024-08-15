#pragma once
#include "EliteEnemyState.h"

class EliteEnemyIdle:public EliteEnemyState
{
	private:
	explicit EliteEnemyIdle() = default;
	virtual ~EliteEnemyIdle() = default;
public:
	// DefaultEnemyState을(를) 통해 상속됨
int Update(const float& deltaTime) override;
int LateUpdate(const float& deltaTime) override;
void OnStart() override;
void OnExit() override;

private:
	EliteEnemy::FSM SelectNextBehave();
private:
	bool CheckAttackRange(int x, int y);

public:
	static EliteEnemyIdle* Create(EliteEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	EliteEnemy::FSM _nextState = EliteEnemy::FSM::None;
	bool _checkState = false;
};

