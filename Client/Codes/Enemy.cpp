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

#include "Tile.h"

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
	transform.position=_movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);

}

void Enemy::Update(const float& deltaTime)
{

	

}

void Enemy::LateUpdate(const float& deltaTime)
{

}