#include "Player.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

// Component
#include "Animation.h"
#include "FiniteStateMachine.h"
#include "Grid.h"
#include "GridMovement.h"


#include "Tile.h"

#include "Client_Define.h"



Player::Player(const wchar_t* name, const Vector3& startPos)
	: MonoBehavior(name),_startPosition(startPos)
{
}

void Player::Awake()
{
	
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Player_Player"))
		throw std::runtime_error("can't load animation!");

	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);
	pSpriteRenderer->SetDrawOffset(Vector3(-10.f, -50.f, 0.f));
	_movement=AddComponent<GridMovement>(L"GridMovement",500.f);

}

void Player::Start()
{
	_gridPosition = _startPosition;
	transform.position=_movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);
}

void Player::Update(const float& deltaTime)
{
	DefaultMove(deltaTime);
}

void Player::LateUpdate(const float& deltaTime)
{
}

void Player::DefaultMove(const float& deltaTime)
{
	Vector3 tempGridPosition = _gridPosition;

	if (Input::IsKeyDown(DIK_D) && !(_movement->_isMoving))
	{
		_gridPosition.x++;
	}
	else if (Input::IsKeyDown(DIK_A) && !(_movement->_isMoving))
	{
		_gridPosition.x--;
	}
	else if (Input::IsKeyDown(DIK_W) && !(_movement->_isMoving))
	{
		_gridPosition.y--;
	}
	else if (Input::IsKeyDown(DIK_S) && !(_movement->_isMoving))
	{
		_gridPosition.y++;
	}
	_gridPosition.x = std::clamp(_gridPosition.x, 0.f, (float)(_movement->_grid->GetTiles()[0].size() - 1));
	_gridPosition.y = std::clamp(_gridPosition.y, 0.f, (float)(_movement->_grid->GetTiles().size() - 1));

	if (_movement->_grid->IsTileWalkable((int)_gridPosition.x, (int)_gridPosition.y))
	{
		_movement->MoveToCell(_gridPosition, 0.5f);
		Tile* prevTile = _movement->_grid->GetTiles()[(int)tempGridPosition.y][(int)tempGridPosition.x];
		prevTile->canMove = true;
	}
	else
	{
		_gridPosition = tempGridPosition;
	}

	Tile* currTile = _movement->_grid->GetTiles()[(int)_gridPosition.y][(int)_gridPosition.x];
	currTile->canMove = false;
}

