#pragma once
#include "EliteEnemyState.h"
class EliteEnemyGetShield:public EliteEnemyState
{
private:
	explicit EliteEnemyGetShield() = default;
	virtual ~EliteEnemyGetShield() = default;
public:
	// EliteEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static EliteEnemyGetShield* Create(EliteEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
	bool _directionCheck = false;
};

