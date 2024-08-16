#include "Player.h"
#include "SpriteRenderer.h"
#include "InputManager.h"

// Component
#include "Animation.h"
#include "Grid.h"
#include "GridMovement.h"
#include "Attribute.h"
#include "HP.h"
#include "PlayerMP.h"
#include "CardSystem.h"
#include "Collider.h"
#include "TimerSystem.h"
#include "HPHUD.h"
#include "JobQueue.h"
#include "AttackCollider.h"
#include "Spectrum.h"
#include "AttributeHUD.h"

// Object
#include "Tile.h"

#include "CardManager.h"
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

	// �ִϸ��̼�
	_pAnimation->ChangeAnimation(L"Idle");
	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->BindAnimation(_pAnimation);
	pSpriteRenderer->SetDrawOffset(Vector3(20.f, -100.f, 0.f));

	_movement = AddComponent<GridMovement>(L"GridMovement", 500.f);

	// System
	_pCardSystem = AddComponent<CardSystem>();
	_pHP = AddComponent<HP>(L"HP", 5);
	_pAttribute = AddComponent<Attribute>();
	_pTimerSystem = AddComponent<TimerSystem>();
	AddComponent<JobQueue>();
	_pAttackCollider = AddComponent<AttackCollider>();
	_pSpectrum = AddComponent<Spectrum>(0.04f, Vector3(20.f, -100.f, 0.f), Vector3(1.f, 1.f, 1.f));

	// UI
	_pMP = AddComponent<PlayerMP>(L"MP");
	HPHUD* pHPHUD = AddComponent<HPHUD>(_pHP, 0);
	pHPHUD->SetDontDestroyObjectUI(true);
	AttributeHUD* pAttHUD = AddComponent<AttributeHUD>(_pAttribute);
	pAttHUD->SetDontDestroyObjectUI(true);

	// �ܻ� ǥ�ÿ�
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

				if (0.f > transform.scale.x)
					position.x *= -1.f;

				pSpriteRenderer->SetDrawOffset(offset + position);
				pSpriteRenderer->Draw();
			}
		});

	// ����Ʈ�� �ִϸ��̼� ���ε�
	Engine::Animation::FrameEvent frameEvent;
	frameEvent.activeFrame = 5;
	frameEvent.animation = L"Dash";
	frameEvent.isRepeat = true;
	frameEvent.function = [=]() { _pSpectrum->SetActive(true); };
	_pAnimation->AddFrameEvent(frameEvent);

	frameEvent.activeFrame = 8;
	frameEvent.function = [=]() { _pSpectrum->SetActive(false); };
	_pAnimation->AddFrameEvent(frameEvent);
}

void Player::Start()
{
	_gridPosition = _startPosition;
	transform.position = _movement->_grid->GetTileCenter((int)_gridPosition.x, (int)_gridPosition.y);

	// �������� �ٲ� �� ���� ����
	MapInfo info = DataManager::GetInstance()->GetMapInfo(L"Stage1");
	_pAttackCollider->Initialize(L"PlayerAttack", (int)info.width, (int)info.height);
}

void Player::Update(const float& deltaTime)
{
	DefaultMove(deltaTime);

	if (Input::IsKeyDown(DIK_O))
	{
		CardManager::GetInstance()->StartSelectCardScene();
	}
}

void Player::LateUpdate(const float& deltaTime)
{
	// �ִϸ��̼� ���� ����
	if (!_pAnimation->IsCurrAnimation(L"Idle"))
	{
		if (_pAnimation->IsLastFrame())
			_pAnimation->ChangeAnimation(L"Idle");
	}
}

void Player::OnCollisionEnter(Engine::CollisionInfo& info)
{
	if (*info.other == L"Body")
	{		
		HP* pHP = info.other->GetComponent<HP>();

		Attribute* pAttribute = info.other->GetComponent<Attribute>();
		if (nullptr == pAttribute)
			return;

		for (int i = 0; i < 2; i++)
		{
			const AttackCollider::AttackInfo& attackInfo = _pAttackCollider->GetCurrentAttackInfo(i);
			pAttribute->AddState(attackInfo.Attribute, attackInfo.AttributeStack);

			int damage = 0;

			if (attackInfo.damage)
			{
				damage = attackInfo.damage + _pAttribute->ActiveHighPower() + pAttribute->ActiveWeakPoint();
			}

			pHP->hp -= damage;
		}

		if (pHP->IsZeroHP())
		{
			if (pAttribute->IsActiveState(AttributeFlag::Extra))
			{
				_pHP->hp += _pAttribute->GetExtraRecoveryValue();
			}
		}
	}

	if (*info.other == L"Attack")
	{
		if (_pAttribute->IsActiveState(AttributeFlag::Shield))
		{
			_pAttribute->UseStack(Attribute::State::Shield);
		}
		else
		{
			_pAttribute->ActiveCharge();

			if (_pAttribute->IsActiveState(AttributeFlag::OverCharge))
			{
				// ���� 8ĭ ����
			}

			for (int i = 0; i < 2; i++)
			{
				const AttackCollider::AttackInfo& attackInfo = info.other->GetComponent<AttackCollider>()->GetCurrentAttackInfo(i);				

				int damage = 0;
				
				if (attackInfo.damage)
					damage = _pAttribute->ActiveWeakPoint() + attackInfo.damage;

				_pAttribute->AddState(attackInfo.Attribute, attackInfo.AttributeStack);
				_pHP->hp -= damage;
			}
		}
	}
}

void Player::OnCollisionExit(Engine::CollisionInfo& info)
{
}

void Player::DefaultMove(const float& deltaTime)
{	
	if (_pTimerSystem->IsStopTime() || !_pAnimation->IsCurrAnimation(L"Idle"))
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
					transform.scale = { 1.f, 1.f, 0.f };
				}
				else if (Input::IsKeyDown(DIK_A))
				{
					_gridPosition.x--;
					transform.scale = { -1.f, 1.f, 0.f };
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

