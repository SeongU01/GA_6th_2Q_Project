#include "GridMovement.h"
#include "Client_Define.h"
#include "Grid.h"
#include "Tile.h"
GridMovement::GridMovement(const wchar_t* name,const float speed)
	:MonoBehavior(name),_moveSpeed(speed)
{
}

void GridMovement::Awake()
{

}

void GridMovement::Start()
{
	SetGrid();
}

void GridMovement::Update(const float& deltaTime)
{
  if (_isMoving)
  {
    _elapsedTime += deltaTime;
    float t = _elapsedTime / _timeToMove;
    if (t >= 1.0f)
    {
      t = 1.0f;
      _isMoving = false;
      _elapsedTime = 0.f;
    }

    float smoothStep = sin(t * XM_PI / 2);
    Vector3 direction = _targetPos - _originPos;
    Vector3 currentPosition = _originPos + direction * smoothStep;

    transform.position = currentPosition;

    /*if (!_isMoving)
    {
      transform.position = _targetPos;
    }*/
  }
}
void GridMovement::LateUpdate(const float& deltaTime)
{
}

void GridMovement::SetGrid()
{
	_originPos = { 0.f,0.f,0.f };
	_targetPos = _originPos;
	Engine::GameObject* pObject = Engine::FindObject((int)LayerGroup::Tile, L"Tile", L"Map");
	if (nullptr != pObject)
	{
		_grid = pObject->GetComponent<Grid>();
	}

    _isMoving = false;

}


void GridMovement::MoveToCell(const Vector3& pos, float timeToMove)
{
	if (_grid != nullptr && _grid->IsTileWalkable((int)pos.x, (int)pos.y) && !_isMoving)
	{
		_originPos = transform.position;
    _grid->GetTiles()[(int)_grid->GetCurrGrid(_originPos).y][(int)_grid->GetCurrGrid(_originPos).x]->canMove = true;
		_targetPos = _grid->GetTileCenter((int)pos.x, (int)pos.y);
    _grid->GetTiles()[(int)pos.y][(int)pos.x]->canMove = false;
		_timeToMove = timeToMove;
		_isMoving = true;
		_elapsedTime = 0.f;
	}
}