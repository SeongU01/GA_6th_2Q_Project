#include "Map.h"
#include "Grid.h"

void Map::Initialize(MapInfo& _mapInfo,const Vector3& position)
{
	AddComponent<Grid>(L"Grid",_mapInfo,position);
	SetName(L"Map");
	SetRenderGroup(0);
}

Map* Map::Create(MapInfo& _mapInfo, const Vector3& position )
{
	Map* pInstance = new Map();
	pInstance->Initialize(_mapInfo,position);
	return pInstance;
}
