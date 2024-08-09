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

class Pannel;
struct ToolTipInfo {
	std::wstring _id;
	std::wstring _title;
	std::wstring _content;
	bool _leftTop;
	Pannel* _pannel;
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
	void Free() override;

	MapInfo GetMapInfo(std::wstring _stageName) 
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

	ObjectArrangeInfo GetObjectInfo(std::wstring _stageName)
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

	ToolTipInfo GetToolTipInfo(std::wstring _name)
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
private:
	std::vector<MapInfo> _mapInfos;
	std::vector<ObjectArrangeInfo>_objectArrangeInfos;
	std::vector<EnemySpawnInfo>_enemySpawnInfos;
	std::vector<ToolTipInfo>_ToolTipInfos;
};
