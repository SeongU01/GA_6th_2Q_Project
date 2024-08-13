#pragma once
#include "DefaultEnemyState.h"
class UI;

class DefaultEnemyMove:public DefaultEnemyState
{
private:
	explicit DefaultEnemyMove() = default;
	virtual ~DefaultEnemyMove() = default;
public:
	// DefaultEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;

	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static DefaultEnemyMove* Create(DefaultEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;	
	bool _isStateOn = false;
};

