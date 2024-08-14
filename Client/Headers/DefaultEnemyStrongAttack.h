#pragma once
#include "DefaultEnemyState.h"
class DefaultEnemyStrongAttack:public DefaultEnemyState
{
private:
	explicit DefaultEnemyStrongAttack() = default;
	virtual ~DefaultEnemyStrongAttack() = default;
public:
	// DefaultEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
	
	void ShowAttackRange();

	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static DefaultEnemyStrongAttack* Create(DefaultEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
};

