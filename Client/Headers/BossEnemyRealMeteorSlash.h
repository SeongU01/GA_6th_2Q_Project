#pragma once
#include "BossEnemyState.h"
class BossEnemyRealMeteorSlash :public BossEnemyState
{
private:
	explicit BossEnemyRealMeteorSlash() = default;
	virtual ~BossEnemyRealMeteorSlash() = default;
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
	static BossEnemyRealMeteorSlash* Create(BossEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
	bool _directionCheck = false;
};


