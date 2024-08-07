#pragma once
#include "Base.h"



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

class MapManager:public Engine::Base,public Engine::SingleTon<MapManager>
{
	friend class SingleTon;
private:
	explicit MapManager() = default;
	virtual ~MapManager() = default;
public:
	bool LoadMap(const wchar_t* filePath);
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
private:
	std::vector<MapInfo> _mapInfos;
};

