#pragma once
#include "DefaultEnemyState.h"
class DefaultEnemyWeakAttack:public DefaultEnemyState
{
private:
	explicit DefaultEnemyWeakAttack() = default;
	virtual ~DefaultEnemyWeakAttack() = default;
public:
	// DefaultEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static DefaultEnemyWeakAttack* Create(DefaultEnemyScript* pScript);
};

