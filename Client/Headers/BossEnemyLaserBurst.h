#pragma once
#include "BossEnemyState.h"
class BossEnemyLaserBurst :public BossEnemyState
{
private:
	explicit BossEnemyLaserBurst() = default;
	virtual ~BossEnemyLaserBurst() = default;
public:
	// BossEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
	void Attack();
	void ShowAttackRange();
public:
	static BossEnemyLaserBurst* Create(BossEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	float _relaxTime = 0.f;
	bool _useAttack = false;
	bool _isStateOn = false;
	bool _directionCheck = false;
};


