#pragma once
#include "DefaultEnemyState.h"
class DefaultEnemyWeakAttack:public DefaultEnemyState
{
private:
	explicit DefaultEnemyWeakAttack() = default;
	virtual ~DefaultEnemyWeakAttack() = default;
public:
	// DefaultEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static DefaultEnemyWeakAttack* Create(DefaultEnemyScript* pScript);
};

