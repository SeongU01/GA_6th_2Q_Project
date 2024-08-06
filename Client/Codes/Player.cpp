#include "Player.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

// Component
#include "Animation.h"
#include "FiniteStateMachine.h"
#include "Grid.h"
#include "GridMovement.h"


#include "Client_Define.h"

Player::Player(const wchar_t* name)
	: MonoBehavior(name)
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

	_movement=AddComponent<GridMovement>(L"GridMovement",700.f);

}

void Player::Start()
{
	transform->SetPosition(_movement->_grid->GetTileCenter(_gridPosition.x, _gridPosition.y));

}

void Player::Update(const float& deltaTime)
{
	if (Input::IsKeyDown(DIK_D)&&!(_movement->_isMoving))
	{
		_gridPosition.x++;
		_movement->MoveToCell(_gridPosition, 0.5f);
	}
	else if (Input::IsKeyDown(DIK_A)&&!(_movement->_isMoving))
	{
		_gridPosition.x--;
		_movement->MoveToCell(_gridPosition, 0.5f);
	}
	else if (Input::IsKeyDown(DIK_W)&&!(_movement->_isMoving))
	{
		_gridPosition.y--;
		_movement->MoveToCell(_gridPosition, 0.5f);
	}
	else if (Input::IsKeyDown(DIK_S)&&!(_movement->_isMoving))
	{
		_gridPosition.y++;
		_movement->MoveToCell(_gridPosition, 0.5f);
	}
}

void Player::LateUpdate(const float& deltaTime)
{
}