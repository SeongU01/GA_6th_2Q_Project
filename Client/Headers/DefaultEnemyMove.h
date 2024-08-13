#pragma once
#include "DefaultEnemyState.h"
class DefaultEnemyMove:public DefaultEnemyState
{
private:
	explicit DefaultEnemyMove() = default;
	virtual ~DefaultEnemyMove() = default;
public:
	// DefaultEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	static DefaultEnemyMove* Create(DefaultEnemyScript* pScript);
};

