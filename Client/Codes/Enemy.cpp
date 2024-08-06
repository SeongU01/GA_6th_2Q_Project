#include "Enemy.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

// Component
#include "Animation.h"
#include "FiniteStateMachine.h"
#include "Grid.h"
#include "GridMovement.h"


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

}

void Enemy::Start()
{
	transform->SetPosition(_movement->_grid->GetTileCenter(_gridPosition.x, _gridPosition.y));
	//이런식으로 그리드 정보 가져올거임
	/*Engine::GameObject* pObject = Engine::FindObject((int)LayerGroup::Tile, "Tile", "Map");
	Grid* pGrid = pObject->GetComponent<Grid>();*/
}

void Enemy::Update(const float& deltaTime)
{
}

void Enemy::LateUpdate(const float& deltaTime)
{
}