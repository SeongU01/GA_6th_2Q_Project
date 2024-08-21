#pragma once
#include "BossEnemyState.h"
class BossEnemySpawnRange:public BossEnemyState
{
private:
	explicit BossEnemySpawnRange() = default;
	virtual ~BossEnemySpawnRange() = default;
public:
	// BossEnemyState을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	void OnStart() override;
	void OnExit() override;
public:
	virtual void ShowInfo();
	virtual void CloseInfo();
	void Spawn();
	void ShowSpawnRange();
	void SpawnEffect(const Vector3& Position);
public:
	static BossEnemySpawnRange* Create(BossEnemyScript* pScript);
private:
	float _currTime = 0.f;
	float _delayTime = 0.f;
	bool _isStateOn = false;
	bool _directionCheck = false;
	int _spawnCount = 0;
};


