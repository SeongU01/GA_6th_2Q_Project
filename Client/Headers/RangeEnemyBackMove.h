#pragma once
#include "RangeEnemyState.h"
class UI;

class RangeEnemyBackMove :public RangeEnemyState
{
private:
	explicit RangeEnemyBackMove() = default;
	virtual ~RangeEnemyBackMove() = default;
public:
	// DefaultEnemyState��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
	Vector3 FindBFS(int step);
	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static RangeEnemyBackMove* Create(RangeEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
};

