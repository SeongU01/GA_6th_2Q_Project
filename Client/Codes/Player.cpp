#include "Player.h"

// Component
#include "RigidBody2D.h"
#include "FiniteStateMachine.h"

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

	_pFSM = AddComponent<Engine::FiniteStateMachine>("FSM", 5);
}

void Player::Start()
{
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