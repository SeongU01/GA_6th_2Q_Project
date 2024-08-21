#pragma once
#include "BossEnemyState.h"
class BossEnemyDeath :public BossEnemyState
{
private:
	explicit BossEnemyDeath() = default;
	virtual ~BossEnemyDeath() = default;
public:
	// BossEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static BossEnemyDeath* Create(BossEnemyScript* pScript);
};
