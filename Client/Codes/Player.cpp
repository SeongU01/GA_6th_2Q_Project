#include "Player.h"

// Component
#include "RigidBody2D.h"
#include "FiniteStateMachine.h"
#include "Grid.h"

#include "Client_Define.h"

Player::Player(const char* name)
	: MonoBehavior(name)
{
}

void Player::Awake()
{
	_pRigidbody = AddComponent<Engine::Rigidbody2D>("Rigidbody");
	_pRigidbody->maxVelocity = Vector3(1000.f, 1000.f, 0.f);
	_pRigidbody->friction = 3000.f;
}

void Player::Start()
{
	//이런식으로 그리드 정보 가져올거임
	/*Engine::GameObject* pObject = Engine::FindObject((int)LayerGroup::Tile, "Tile", "Map");
	Grid* pGrid = pObject->GetComponent<Grid>();*/
}

void Player::Update(const float& deltaTime)
{
	float horizon = Input::GetAxis(Input::Horizontal);
	float vertical = Input::GetAxis(Input::Vertical);
	float movespeed = 100.f;

	_pRigidbody->velocity += Vector3(horizon * movespeed, vertical * movespeed, 0.f);
}

void Player::LateUpdate(const float& deltaTime)
{
}