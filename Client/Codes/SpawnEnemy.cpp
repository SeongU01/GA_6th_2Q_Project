#include "SpawnEnemy.h"
#include "GridInfo.h"
#include "Grid.h"
//Object
#include "DefaultEnemy.h"

#include "Client_Define.h"

SpawnEnemy::SpawnEnemy(const wchar_t* name, const EnemySpawnInfo& _spawnInfo)
	:MonoBehavior(name)
{
	_currSpawnInfo = _spawnInfo;
}

void SpawnEnemy::Awake()
{
	_maxWaveCount = (int)_currSpawnInfo.waveInfos.size();
	_pGridInfo = AddComponent<GridInfo>(L"GridInfo");
}

void SpawnEnemy::Start()
{
	_currWaveCount++;
	_currWave = DataManager::GetInstance()->GetWaveInfo(_currSpawnInfo, L"Wave"+std::to_wstring(_currWaveCount));
}

void SpawnEnemy::Update(const float& deltaTime)
{
	if (!_waveOn && _currWaveCount <= _maxWaveCount&&!_stageEnd)
	{
		for (auto& _enemyInfo : _currWave.enemyInfos)
		{
			if(L"Default"==_enemyInfo.spawnType)
			{
				Vector3 spawnPos;

				if (_pGridInfo->GetGrid()->IsTileWalkable((int)_enemyInfo.spawnPosition.x, (int)_enemyInfo.spawnPosition.y)==true)
				{
					spawnPos = { _enemyInfo.spawnPosition.x, _enemyInfo.spawnPosition.y ,0.f};
				}
				else
				{
					spawnPos = { _enemyInfo.subSpawnPosition.x, _enemyInfo.subSpawnPosition.y, 0.f};
				}
					
				DefaultEnemy* defaultEnemy = DefaultEnemy::Create(spawnPos, _enemyInfo.targetName);
				Engine::AddObjectInLayer((int)LayerGroup::Enemy, L"Monster", defaultEnemy);
			}
		}

		_waveOn = true;
	}

	if(!_stageEnd)
	{
		CheckWaveEnd();
	}
}

void SpawnEnemy::LateUpdate(const float& deltaTime)
{
}

void SpawnEnemy::CheckWaveEnd()
{
	if (Engine::FindObjectList((int)LayerGroup::Enemy, L"Monster")->empty()&&!_stageEnd)
	{
		_waveOn = false;
		_currWaveCount++;
		if (_currWaveCount > _maxWaveCount)
		{
			_stageEnd = true;
		}
		if(!_stageEnd)
			_currWave = DataManager::GetInstance()->GetWaveInfo(_currSpawnInfo, L"Wave" + std::to_wstring(_currWaveCount));
	}
}
