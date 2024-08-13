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

private:
	int SelectNextBehave();
private:
	bool CheckAttackRange(int arrange);
public:
	static DefaultEnemyIdle* Create(DefaultEnemyScript* pScript);

private:
	float _delayTime = 0.f;
};

