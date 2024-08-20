#pragma once
#include "BossEnemyState.h"

class BossEnemyMove :public BossEnemyState
{
private:
	explicit BossEnemyMove() = default;
	virtual ~BossEnemyMove() = default;
public:
	// BossEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static BossEnemyMove* Create(BossEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
};


