#include "EnemySpawner.h"
#include "DataManager.h"

//script
#include "SpawnEnemy.h"

#include "Client_Define.h"
void EnemySpawner::Initialize(const EnemySpawnInfo& _enemyInfo)
{
	AddComponent<SpawnEnemy>(L"SpawnEnemy", _enemyInfo);
	SetRenderGroup((int)RenderGroup::None);
}

EnemySpawner* EnemySpawner::Create(const EnemySpawnInfo& _enemyInfo)
{
	EnemySpawner* pInstance = new EnemySpawner;
	pInstance->Initialize(_enemyInfo);

	return pInstance;
}
