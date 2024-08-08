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
struct ObjectArrangeInfo
{
	std::wstring stageName;
	std::vector<std::pair<int, Vector3>> objectPositionInfo;
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
		for (const auto& objInfo : _objectInfo)
		{
			if (objInfo.stageName == _stageName)
			{
				return objInfo;
			}
		}
		throw std::runtime_error("Stage not found");
	}
private:
	std::vector<MapInfo> _mapInfos;
	std::vector<ObjectArrangeInfo>_objectInfo;
};

