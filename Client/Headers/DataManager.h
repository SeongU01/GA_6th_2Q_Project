#pragma once
#include "Base.h"


//map
struct MapInfo
{
	std::wstring stageName;
	float mapOffsetY = 0.f;
	float tileOffsetX = 0.f;
	float tileOffsetY = 0.f;
	float width=0;
	float height=0;
	std::vector<std::vector<int>>mapData;
};

//object
struct ObjectInfo
{
	int objectID=-1;
	Vector3 objectPosition = {0.f,0.f,0.f};
	std::wstring objectTag;
};
struct ObjectArrangeInfo
{
	std::wstring stageName;
	std::vector<ObjectInfo> objectInfos;
};

//enemy wave
struct EnemyInfo
{
	Vector3 spawnPosition = { 0.f,0.f ,0.f };
	Vector3 subSpawnPosition = { 0.f,0.f ,0.f };
	std::wstring targetName;
	std::wstring spawnType;
};
struct WaveInfo
{
	std::wstring waveName;
	std::vector<EnemyInfo>enemyInfos;
};
struct EnemySpawnInfo
{
	std::wstring stageName;
	std::vector<WaveInfo> waveInfos;
};

struct ToolTipInfo {
	std::wstring _id;
	std::wstring _title;
	std::wstring _content;
	bool _leftTop;
};

struct CutSceneInfo {
	int _part; 
	int _order;
	float _duration;
	std::wstring _voiceTag;
	std::wstring _dummySoundTag;
};

class DataManager:public Engine::Base,public Engine::SingleTon<DataManager>
{
	friend class SingleTon;
private:
	explicit DataManager() = default;
	virtual ~DataManager() = default;
public:
	bool LoadMap(const wchar_t* filePath);
	bool LoadObjectArrange(const wchar_t* filePath);
	bool LoadEnemySpawn(const wchar_t* filePath);
	bool LoadToolTip(const wchar_t* filePath);	
	bool LoadCutScene(const wchar_t* filePath);
	bool LoadAttackRangeData(const wchar_t* filePath);
	void Free() override;

	const MapInfo& GetMapInfo(std::wstring _stageName) 
	{
		for (const auto& mapInfo : _mapInfos) 
		{
			if (mapInfo.stageName == _stageName) 
			{
				return mapInfo;
			}
		}
		throw std::runtime_error("Stage not found");
	}

	const ObjectArrangeInfo& GetObjectInfo(std::wstring _stageName)
	{
		for (const auto& objInfo : _objectArrangeInfos)
		{
			if (objInfo.stageName == _stageName)
			{
				return objInfo;
			}
		}
		throw std::runtime_error("Stage not found");
	}

	const ToolTipInfo& GetToolTipInfo(std::wstring _name)
	{
		for (const auto& objInfo : _ToolTipInfos)
		{
			if (objInfo._id == _name)
			{
				return objInfo;
			}
		}
		throw std::runtime_error("Stage not found");
	}
	
	const EnemySpawnInfo& GetEnemySpawnInfo(std::wstring _stageName)
	{
		for (const auto& spawnInfo : _enemySpawnInfos)
		{
			if (spawnInfo.stageName == _stageName)
			{
				return spawnInfo;
			}
		}
		throw std::runtime_error("Stage not found");
	}
	const WaveInfo& GetWaveInfo(const EnemySpawnInfo& spawnInfo, const std::wstring& waveName) 
	{

		for (const auto& waveInfo : spawnInfo.waveInfos) 
		{
			if (waveInfo.waveName == waveName)
			{
				return waveInfo;
			}
		}
		throw std::runtime_error("Wave not found");
	}

	CutSceneInfo GetCutSceneInfo(int part, int order)
	{
		for (const auto& objInfo : _CutSceneInfos)
		{
			if (objInfo._part == part && objInfo._order ==order)
			{
				return objInfo;
			}
		}
		CutSceneInfo info;
		info._part = 0;
		return info;
	}


	const std::vector<std::pair<int, int>>& GetAttackRange(int ID) const { return _attackRanges[ID]; }

private:
	std::vector<MapInfo> _mapInfos;
	std::vector<ObjectArrangeInfo>_objectArrangeInfos;
	std::vector<EnemySpawnInfo>_enemySpawnInfos;
	std::vector<ToolTipInfo>_ToolTipInfos;
	std::vector<std::vector<std::pair<int, int>>> _attackRanges;
	std::vector<CutSceneInfo> _CutSceneInfos;
};
