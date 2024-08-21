#pragma once
#include "RangeEnemyState.h"
class RangeEnemyDeath :public RangeEnemyState
{
private:
	explicit RangeEnemyDeath() = default;
	virtual ~RangeEnemyDeath() = default;
public:
	// RangeEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static RangeEnemyDeath* Create(RangeEnemyScript* pScript);
};
