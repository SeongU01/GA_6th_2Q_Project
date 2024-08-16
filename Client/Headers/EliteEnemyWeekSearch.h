#pragma once
#include "EliteEnemyState.h"
class EliteEnemyWeekSearch :public EliteEnemyState
{
private:
	explicit EliteEnemyWeekSearch() = default;
	virtual ~EliteEnemyWeekSearch() = default;
public:
	// EliteEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
	void ShowAttackRange();
public:
	static EliteEnemyWeekSearch* Create(EliteEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
	bool _directionCheck = false;
};

