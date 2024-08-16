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
virtual void ShowInfo();
virtual void CloseInfo();
private:
	EliteEnemy::FSM SelectNextBehave();
private:

public:
	static EliteEnemyIdle* Create(EliteEnemyScript* pScript);
private:
	bool _getShield=false;
	float _currTime = 0.f;
	float _delayTime = 0.f;
	EliteEnemy::FSM _nextState = EliteEnemy::FSM::None;
	bool _checkState = false;
	int _count = 0;
};

