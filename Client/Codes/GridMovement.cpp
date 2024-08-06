#include "GridMovement.h"
#include "Client_Define.h"
#include "Grid.h"
GridMovement::GridMovement(const wchar_t* name)
	:MonoBehavior(name)
{
}

void GridMovement::Awake()
{

}

void GridMovement::Start()
{
	_originPos = transform->position;
	_targetPos = _originPos;
	Engine::GameObject* pObject=Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map");
	if (nullptr != pObject)
	{
		_grid = pObject->GetComponent<Grid>();
	}
}

void GridMovement::Update(const float& deltaTime)
{
	if (_isMoving) 
	{
		float moveStep = deltaTime / _timeToMove;
		Vector3 direction = _targetPos - _originPos;
		direction=XMVector3Normalize(direction);
		_originPos += direction * moveStep;

		if (XMVector3Length(_targetPos - _originPos).m128_f32[0] < 0.01f)
		{
			_originPos = _targetPos;
			_isMoving = false;
		}
		transform->position = _originPos;
	}
}

void GridMovement::LateUpdate(const float& deltaTime)
{
}

void GridMovement::MoveToCell(int x, int y, float timeToMove)
{
	if (_grid->IsTileWalkable(x, y) && !_isMoving)
	{
		_targetPos = _grid->GetTileCenter(x, y);
		_timeToMove = timeToMove;
		_isMoving = true;
	}
 }
