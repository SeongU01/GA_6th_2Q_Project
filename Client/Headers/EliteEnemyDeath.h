#pragma once
#include "EliteEnemyState.h"
class EliteEnemyDeath :public EliteEnemyState
{
private:
	explicit EliteEnemyDeath() = default;
	virtual ~EliteEnemyDeath() = default;
public:
	// EliteEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static EliteEnemyDeath* Create(EliteEnemyScript* pScript);
};

