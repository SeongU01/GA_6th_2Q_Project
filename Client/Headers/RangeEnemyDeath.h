#pragma once
#include "RangeEnemyState.h"
class RangeEnemyDeath :public RangeEnemyState
{
private:
	explicit RangeEnemyDeath() = default;
	virtual ~RangeEnemyDeath() = default;
public:
	// RangeEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static RangeEnemyDeath* Create(RangeEnemyScript* pScript);
};
