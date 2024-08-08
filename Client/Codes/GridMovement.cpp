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

    if (!_isMoving)
    {
      transform.position = _targetPos;
    }
  }
}
void GridMovement::LateUpdate(const float& deltaTime)
{
}


void GridMovement::MoveToCell(Vector3& pos, float timeToMove)
{
	if (_grid != nullptr && _grid->IsTileWalkable((int)pos.x, (int)pos.y) && !_isMoving)
	{
		_originPos = transform.position;
		_targetPos = _grid->GetTileCenter((int)pos.x, (int)pos.y);
		_timeToMove = timeToMove;
		_isMoving = true;
		_elapsedTime = 0.f;
	}
}