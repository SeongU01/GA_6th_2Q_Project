#pragma once
#include "RangeEnemyState.h"
class UI;

class RangeEnemyForwardMove :public RangeEnemyState
{
private:
	explicit RangeEnemyForwardMove() = default;
	virtual ~RangeEnemyForwardMove() = default;
public:
	// DefaultEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;

	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static RangeEnemyForwardMove* Create(RangeEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
};

