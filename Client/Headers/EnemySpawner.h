#pragma once
#include "GameObject.h"

struct EnemySpawnInfo;

class EnemySpawner : public Engine::GameObject
{
private:
	explicit EnemySpawner() = default;
	virtual ~EnemySpawner() = default;

private:
	void Initialize(const EnemySpawnInfo& _enemyInfo);

public:
	static EnemySpawner* Create(const EnemySpawnInfo& _enemyInfo);

};