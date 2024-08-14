#include "Player.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

// Component
#include "Animation.h"
#include "FiniteStateMachine.h"
#include "Grid.h"
#include "GridMovement.h"
#include "AdditiveState.h"
#include "HP.h"
#include "PlayerMP.h"
#include "CombatEvent.h"
#include "CardSystem.h"
#include "Collider.h"
#include "TimerSystem.h"
#include "HPHUD.h"
#include "JobQueue.h"
#include "AttackCollider.h"

// Object
#include "Tile.h"

#include "DataManager.h"
#include "Client_Define.h"

Player::Player(const wchar_t* name, const Vector3& startPos)
	: MonoBehavior(name), _startPosition(startPos)
{
}

void Player::SetGridPostion(const Vector3& position)
{
	Tile* prevTile = _movement->_grid->GetTiles()[(int)_gridPosition.y][(int)_gridPosition.x];
	prevTile->canMove = true;
	_gridPosition = position;
	_nextGridPosition = position;
}

void Player::SetNextGridPosition(const Vector3& position)
{
	_nextGridPosition = position;
}

void Player::ResetPlayer(const Vector3& startPos)
{
	 _movement->SetGrid();
	 _startPosition = startPos;
	 _gridPosition = startPos;
	 transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);
	 GetComponent<TimerSystem>()->ResetTime();
}

void Player::Awake()
{	
	_pAnimation = AddComponent<Engine::Animation>(L"Animation");
	if (false == _pAnimation->LoadAnimation(L"Player_Player"))
		throw std::runtime_error("can't load animation!");

	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);
	pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));
	_movement = AddComponent<GridMovement>(L"GridMovement", 500.f);

	_pMP = AddComponent<PlayerMP>(L"MP");
	_pCardSystem = AddComponent<CardSystem>();
	_pHP = AddComponent<HP>(L"HP", 5);
	_pCombatEvent = AddComponent<CombatEvent>();
	_pAdditiveState = AddComponent<AdditiveState>();
	_pTimerSystem = AddComponent<TimerSystem>();
	AddComponent<JobQueue>();
	_pAttackCollider = AddComponent<AttackCollider>();

	//플레이어 체력바
	Engine::GameObject* pHPHUDDObj = &transform.GetOwner();
	pHPHUDDObj->AddComponent<HPHUD>(_pHP, 0);

	// 잔상 표시용
	pSpriteRenderer = AddComponent<Engine::SpriteRenderer>(L"Dummy");
	pSpriteRenderer->BindAnimation(_pAnimation);
	pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(1.f, 1.f, 1.f, 0.5f);
	pSpriteRenderer->SetOneSelfDraw(true, [=]()
		{
			if (_pTimerSystem->IsStopTime())
			{
				Vector3 offset = { 20.f, -100.f, 0.f };
				Vector3 position = _movement->_grid->GetTileCenter((int)_nextGridPosition.x, (int)_nextGridPosition.y);
				position = position - transform.position;

				pSpriteRenderer->SetDrawOffset(offset + position);
				pSpriteRenderer->Draw();
			}
		});
}

void Player::Start()
{
	//_pHP->SetHP(4);
	_gridPosition = _startPosition;
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);

	// 스테이지 바뀔 때 마다 갱신
	MapInfo info = DataManager::GetInstance()->GetMapInfo(L"Stage1");
	_pAttackCollider->Initialize(L"PlayerAttack", (int)info.width, (int)info.height);
}

void Player::Update(const float& deltaTime)
{
	DefaultMove(deltaTime);
}

void Player::LateUpdate(const float& deltaTime)
{
}

void Player::OnCollisionEnter(Engine::CollisionInfo& info)
{
	if (*info.other == L"Body")
	{
		std::cout << "충돌" << std::endl;

		const AttackCollider::AttackInfo& attackInfo = _pAttackCollider->GetCurrentAttackInfo();
		HP* pHP = info.other->GetComponent<HP>();

		AdditiveState* pAdditiveState = info.other->GetComponent<AdditiveState>();
		pAdditiveState->AddState(attackInfo.additiveState, attackInfo.additiveStateStack);
		
		pHP->hp -= attackInfo.damage + _pAdditiveState->ActiveHighPower();
		
		if (pHP->IsZeroHP())
		{
			if (pAdditiveState->IsActiveState(AdditiveFlag::Extra))
			{
				_pHP->hp += _pAdditiveState->GetExtraRecoveryValue();
			}
		}
	}

	if (*info.other == L"Attack")
	{
		if (_pAdditiveState->IsActiveState(AdditiveFlag::Shield))
		{
			_pAdditiveState->UseStack(AdditiveState::State::Shield);
		}
		else
		{
			_pAdditiveState->ActiveCharge();

			if (_pAdditiveState->IsActiveState(AdditiveFlag::OverCharge))
			{
				// 방전 8칸 공격
			}

			const AttackCollider::AttackInfo& attackInfo = info.other->GetComponent<AttackCollider>()->GetCurrentAttackInfo();
			int damage = _pAdditiveState->ActiveWeakPoint() + attackInfo.damage;
			_pAdditiveState->AddState(attackInfo.additiveState, attackInfo.additiveStateStack);
			_pHP->hp -= damage;
		}
	}	
}

void Player::OnCollisionExit(Engine::CollisionInfo& info)
{
}

void Player::DefaultMove(const float& deltaTime)
{	
	if (_pTimerSystem->IsStopTime())
		return;

	if (nullptr != _movement->_grid)
	{
		Vector3 tempGridPosition = _gridPosition;
		if (!(_movement->_grid->GetTiles().empty())) 
		{
			if (!(_movement->_isMoving))
			{
				/*_gridPosition.x += Input::GetAxis(Input::Axis::Horizontal);
				_gridPosition.y += Input::GetAxis(Input::Axis::Vertical);*/

				if (Input::IsKeyDown(DIK_D))
				{
					_gridPosition.x++;
				}
				else if (Input::IsKeyDown(DIK_A))
				{
					_gridPosition.x--;
				}
				else if (Input::IsKeyDown(DIK_W))
				{
					_gridPosition.y--;
				}
				else if (Input::IsKeyDown(DIK_S))
				{
					_gridPosition.y++;
				}
			}

			_gridPosition.x = std::clamp(_gridPosition.x, 0.f, (float)(_movement->_grid->GetTiles()[0].size() - 1));
			_gridPosition.y = std::clamp(_gridPosition.y, 0.f, (float)(_movement->_grid->GetTiles().size() - 1));

			if (_movement->_grid->IsTileWalkable((int)_gridPosition.x, (int)_gridPosition.y))
			{
				_movement->MoveToCell(_gridPosition, 0.25f);
				Tile* prevTile = _movement->_grid->GetTiles()[(int)tempGridPosition.y][(int)tempGridPosition.x];
				prevTile->canMove = true;
			}
			else
			{
				_gridPosition = tempGridPosition;
			}

			_nextGridPosition = _gridPosition;
			Tile* currTile = _movement->_grid->GetTiles()[(int)_gridPosition.y][(int)_gridPosition.x];
			currTile->canMove = false;
		}
	}
}

