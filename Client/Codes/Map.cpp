#include "Map.h"
#include "Grid.h"

void Map::Initialize(const MapInfo& _mapInfo,const Vector3& position)
{
	AddComponent<Grid>(L"Grid",_mapInfo,position);
	SetName(L"Map");
	SetRenderGroup(0);
}

Map* Map::Create(const MapInfo& _mapInfo, const Vector3& position)
{
	Map* pInstance = new Map();
	pInstance->Initialize(_mapInfo,position);
	return pInstance;
}
