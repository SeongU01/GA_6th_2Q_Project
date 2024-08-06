#pragma once
#include "Base.h"

struct MapInfo
{
	
};

class MapManager:public Engine::Base,public Engine::SingleTon<MapManager>
{
private:
	explicit MapManager() = default;
	virtual ~MapManager() = default;
public:
	bool LoadMap(const wchar_t* filePath);
	void Free() override;
private:
	std::vector<MapInfo> _mapInfo;
};

