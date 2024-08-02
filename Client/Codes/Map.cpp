#include "Map.h"
#include "Grid.h"

void Map::Initialize(const Vector3& matrix, const Vector3& offset, const Vector3& position)
{
	AddComponent<Grid>("Grid", matrix, offset,position);
	SetName("Map");
	SetRenderGroup(0);
}

Map* Map::Create(const Vector3& matrix, const Vector3& offset, const Vector3& position)
{
	Map* pInstance = new Map();
	pInstance->Initialize(matrix, offset,position);
	return pInstance;
}
