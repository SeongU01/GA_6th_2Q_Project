#pragma once
#include "GameObject.h"
#include "MapManager.h"

class Map :public Engine::GameObject
{
private:
	explicit Map() = default;
	virtual ~Map() = default;
private:
	void Initialize(MapInfo& _mapInfo, const Vector3& position);
public:
	static Map* Create(MapInfo& _mapInfo, const Vector3& position );
};

