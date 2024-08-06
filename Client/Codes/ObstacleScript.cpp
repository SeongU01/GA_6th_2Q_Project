#include "ObstacleScript.h"
#include "GridInfo.h"
#include "Grid.h"
#include "Tile.h"
ObstacleScript::ObstacleScript(const wchar_t* name, const std::pair<Vector3, Vector3>& gridRange)
	:MonoBehavior(name), _gridRange(gridRange)
{
}

void ObstacleScript::Awake()
{
	_pGridInfo = AddComponent<GridInfo>(L"GridInfo");
}

void ObstacleScript::Start()
{

	float x = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).x +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).x) / 2;
	float y = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).y +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).y) / 2;

	transform->SetPosition(Vector3(x,y,0.f));
	for (int y = (int)_gridRange.first.y; y < (int)_gridRange.second.y + 1; y++)
	{
		for (int x = (int)_gridRange.first.x; x < (int)_gridRange.second.x + 1; x++)
		{
			_pGridInfo->GetGrid()->GetTiles()[y][x]->canMove = false;
		}
	}
}

void ObstacleScript::Update(const float& deltaTime)
{
}

void ObstacleScript::LateUpdate(const float& deltaTime)
{
}
