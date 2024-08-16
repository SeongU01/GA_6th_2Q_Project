#pragma once
#include "EliteEnemyState.h"
class EliteEnemyDeath :public EliteEnemyState
{
private:
	explicit EliteEnemyDeath() = default;
	virtual ~EliteEnemyDeath() = default;
public:
	// EliteEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static EliteEnemyDeath* Create(EliteEnemyScript* pScript);
};

