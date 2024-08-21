#pragma once
#include "RangeEnemyState.h"
class RangeEnemyMove :public RangeEnemyState
{
private:
	explicit RangeEnemyMove() = default;
	virtual ~RangeEnemyMove() = default;
public:
	// RangeEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static RangeEnemyMove* Create(RangeEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
};


