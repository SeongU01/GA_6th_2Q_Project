#pragma once
#include "EliteEnemyState.h"
class EliteEnemyMove:public EliteEnemyState
{
private:
	explicit EliteEnemyMove() = default;
	virtual ~EliteEnemyMove() = default;
public:
	// EliteEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
public:
	static EliteEnemyMove* Create(EliteEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
};

