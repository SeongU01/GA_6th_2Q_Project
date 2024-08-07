#include "Enemy.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

// Component
#include "Animation.h"
#include "FiniteStateMachine.h"
#include "Grid.h"
#include "GridMovement.h"
#include "GameObject.h"
#include "Astar.h"

#include "Client_Define.h"

Enemy::Enemy(const wchar_t* name)
	: MonoBehavior(name)
{
}

void Enemy::Awake()
{
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Player_Player"))
		throw std::runtime_error("can't load animation!");

	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);

	_movement = AddComponent<GridMovement>(L"GridMovement", 300.f);
	Engine::GameObject* players= Engine::FindObject((int)LayerGroup::Player, L"Player",NULL);
	_player = players->GetComponent<Player>();
}

void Enemy::Start()
{
	transform->SetPosition(_movement->_grid->GetTileCenter(_gridPosition.x, _gridPosition.y));

}

void Enemy::Update(const float& deltaTime)
{

	Vector3 temporaryGoal = _player->GetGridPosition(); // 목표 지점
    static std::vector<Vector3> path;
    static size_t pathIndex = 0;
    _curTime += deltaTime;

    if (!(temporaryGoal == goalPosition)||path.empty() || pathIndex >= path.size()) {
		goalPosition = temporaryGoal;
        path = aStar(_gridPosition, goalPosition, _movement->_grid->GetTiles());
        pathIndex = 1;
    }

    if (!path.empty() && pathIndex < path.size()) {
        Vector3 nextPosition = path[pathIndex];
        if (_curTime >= _moveTime) {
            _curTime = 0.0f;
            _gridPosition = nextPosition;
            pathIndex++;
        }
    }

	_gridPosition.x = std::clamp(_gridPosition.x, 0.f, (float)(_movement->_grid->GetTiles()[0].size() - 1));
	_gridPosition.y = std::clamp(_gridPosition.y, 0.f, (float)(_movement->_grid->GetTiles().size() - 1));

	if (_movement->_grid->IsTileWalkable((int)_gridPosition.x, (int)_gridPosition.y))
	{
		_movement->MoveToCell(_gridPosition, 0.5f);
	}
	else
	{
		path.clear();
		//_gridPosition = tempGridPosition;
	}
}

void Enemy::LateUpdate(const float& deltaTime)
{

}