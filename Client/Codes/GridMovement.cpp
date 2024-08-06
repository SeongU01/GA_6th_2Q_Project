#include "GridMovement.h"
#include "Client_Define.h"
#include "Grid.h"
GridMovement::GridMovement(const wchar_t* name,const float speed)
	:MonoBehavior(name),_moveSpeed(speed)
{
}

void GridMovement::Awake()
{

}

void GridMovement::Start()
{
	_originPos = { 0.f,0.f,0.f };
	_targetPos = _originPos;
	Engine::GameObject* pObject = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map");
	if (nullptr != pObject)
	{
		_grid = pObject->GetComponent<Grid>();
	}
}

void GridMovement::Update(const float& deltaTime)
{
	if (_isMoving)
	{
		_elapsedTime += deltaTime;
		_originPos = transform->position;
		float t = _elapsedTime / _timeToMove;
		float smoothStep = sin(t * XM_PI);
		float moveStep = deltaTime / _timeToMove;
		Vector3 direction = _targetPos - _originPos;
		direction = XMVector3Normalize(direction);
		_originPos += direction * moveStep*_moveSpeed*smoothStep;

		if (XMVector3Length(_targetPos - _originPos).m128_f32[0] < 0.01f)
		{
			_originPos = _targetPos;
			_isMoving = false;
			_elapsedTime = 0.f;
		}
		transform->position = _originPos;
	}
}

void GridMovement::LateUpdate(const float& deltaTime)
{
}

void GridMovement::MoveToCell(Vector3& pos, float timeToMove)
{
	if (_grid->IsTileWalkable((int)pos.x, (int)pos.y) && !_isMoving)
	{
		_targetPos = _grid->GetTileCenter((int)pos.x, (int)pos.y);
		_timeToMove = timeToMove;
		_isMoving = true;
	}
}
