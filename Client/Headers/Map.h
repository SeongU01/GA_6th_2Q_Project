#pragma once
#include "GameObject.h"
#include "DataManager.h"

class Map :public Engine::GameObject
{
private:
	explicit Map() = default;
	virtual ~Map() = default;
private:
	void Initialize(const MapInfo& _mapInfo, const Vector3& position);
public:
	static Map* Create(const MapInfo& _mapInfo, const Vector3& position);
};

