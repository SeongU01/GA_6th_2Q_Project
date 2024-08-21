#pragma once
#include "BossEnemyState.h"

class BossEnemyIdle :public BossEnemyState
{
private:
	explicit BossEnemyIdle() = default;
	virtual ~BossEnemyIdle() = default;
public:
	// DefaultEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
	virtual void ShowInfo();
	virtual void CloseInfo();
private:
	BossEnemy::FSM SelectNextBehave();
private:

public:
	static BossEnemyIdle* Create(BossEnemyScript* pScript);
private:
	Vector3 _nextTargetPosition = { 0.f,0.f,0.f };
	float _currTime = 0.f;
	float _delayTime = 0.f;
	BossEnemy::FSM _nextState = BossEnemy::FSM::None;
	bool _checkState = false;
	int _anger = 0;
	int _charge = 0;
	float _alpha = 0.f;
	bool _isFandIn = false;
};
