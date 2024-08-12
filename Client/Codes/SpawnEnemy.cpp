#include "SpawnEnemy.h"
#include "GridInfo.h"

//Object
#include "DefaultEnemy.h"

#include "Client_Define.h"

SpawnEnemy::SpawnEnemy(const wchar_t* name, const EnemySpawnInfo& _spawnInfo)
	:MonoBehavior(name)
{
	_pGridInfo = AddComponent<GridInfo>(L"GridInfo");
	_currSpawnInfo = _spawnInfo;
}

void SpawnEnemy::Awake()
{
}

void SpawnEnemy::Start()
{
	_currWave = DataManager::GetInstance()->GetWaveInfo(_currSpawnInfo, L"Wave1");
}

void SpawnEnemy::Update(const float& deltaTime)
{
	if (!_waveOn)
	{
		for (auto& enmeyInfo : _currWave.enemyInfos)
		{
			
			Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"DefaultEnemy",DefaultEnemy::Create());
		}

	}
}

void SpawnEnemy::LateUpdate(const float& deltaTime)
{
}