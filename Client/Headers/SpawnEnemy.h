#pragma once
#include "MonoBehavior.h"
#include "DataManager.h"

class GridInfo;

class SpawnEnemy :public Engine::MonoBehavior
{
public:
	explicit SpawnEnemy(const wchar_t* name, const EnemySpawnInfo& _spawnInfo);
private:
	virtual ~SpawnEnemy() = default;
public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	EnemySpawnInfo _currSpawnInfo;
	WaveInfo _currWave;
	GridInfo* _pGridInfo=nullptr;
	bool _waveOn=false;
	
};
