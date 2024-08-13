#include "DefenseScript.h"
#include "Grid.h"
#include "GridInfo.h"
#include "Tile.h"
#include "HP.h"
#include "SpriteRenderer.h"

#include "Client_Define.h"

DefenseScript::DefenseScript(const wchar_t* name, const std::pair<Vector3, Vector3>& gridRange)
	:MonoBehavior(name), _gridRange(gridRange)
{
}

void DefenseScript::Awake()
{
	_pGridInfo = AddComponent<GridInfo>(L"GridInfo");
	_pHP = GetComponent<HP>(L"HP");
	_pSpriteRenderer = GetComponent<Engine::SpriteRenderer>(L"SpriteRenderer");
}

void DefenseScript::Start()
{
	float x = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).x +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).x) / 2;
	float y = (_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.first.x, (int)_gridRange.first.y).y +
		_pGridInfo->GetGrid()->GetTileCenter((int)_gridRange.second.x, (int)_gridRange.second.y).y) / 2;

	transform.position = Vector3(x, y, 0.f);
	for (int y = (int)_gridRange.first.y; y < (int)_gridRange.second.y + 1; y++)
	{
		for (int x = (int)_gridRange.first.x; x < (int)_gridRange.second.x + 1; x++)
		{
			_pGridInfo->GetGrid()->GetTiles()[y][x]->canMove = false;
		}
	}
	_gridPosition = { _gridRange.second.x, _gridRange.second.y ,0.f };
}

void DefenseScript::Update(const float& deltaTime)
{
}

void DefenseScript::LateUpdate(const float& deltaTime)
{
	_pSpriteRenderer->SetIndex((_pHP->GetMaxHP() - _pHP->hp));
}
