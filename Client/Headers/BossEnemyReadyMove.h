#pragma once
#include "BossEnemyState.h"
class BossEnemyReadyMove :public BossEnemyState
{
private:
	explicit BossEnemyReadyMove() = default;
	virtual ~BossEnemyReadyMove() = default;
public:
	// BossEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
private:
	void GetShield();
	void Boost();
public:
	static BossEnemyReadyMove* Create(BossEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
};


