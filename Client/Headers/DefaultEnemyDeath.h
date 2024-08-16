#pragma once
#include "DefaultEnemyState.h"
class DefaultEnemyDeath:public DefaultEnemyState
{
private:
	explicit DefaultEnemyDeath() = default;
	virtual ~DefaultEnemyDeath() = default;
public:
	// EliteEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static DefaultEnemyDeath* Create(DefaultEnemyScript* pScript);
};

