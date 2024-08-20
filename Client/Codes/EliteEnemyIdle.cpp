#include "EliteEnemyIdle.h"
#include "EliteEnemyScript.h"
//component
#include "Animation.h"
#include "GridMovement.h"
#include "Player.h"
#include "DefenseScript.h"
#include "Astar.h"
#include "HP.h"
#include "Attribute.h"
#include "AttributeHUD.h"
#include "SpriteRenderer.h"

#include "TextRenderer.h"
#include "Client_Define.h"

int EliteEnemyIdle::Update(const float& deltaTime)
{
	if (!_isFandIn)
	{
		_alpha += deltaTime;
		_pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(1.f, 1.f, 1.f, _alpha);
		_pHP->SetInvinsibleTime(1.f);
		_pHP->SetInvinsible(true);
		if (_alpha >= 1.f)
		{
			_alpha = 1.f;
			_pSpriteRenderer->GetShader<Engine::ShaderColor>()->SetColor(1.f, 1.f, 1.f, _alpha);
			_pHP->SetInvinsibleTime(0.1f);
			_pHP->SetInvinsible(false);
			_isFandIn = true;
		}
		return 0;
	}

	_nextState = SelectNextBehave();
	if (CheckRange(5, 2))
	{
		_pTargetPosition = &_pPlayer->GetGridPosition();
		_pAstar->SetGoalPosition(*_pTargetPosition);
		_pAstar->ReCalculatePath();
	}
	else
	{
		_pTargetPosition =&(*_ppDefense)->GetGridPosition();
		_pAstar->SetGoalPosition(*_pTargetPosition);
		_pAstar->ReCalculatePath();
	}
	const Vector3& gridPosition = *_pGridPosition;
	Vector3 Direction = *_pTargetPosition - gridPosition;

	if (_currDirection.x * Direction.x < 0)
	{
		_currDirection.x *= -1;
		_pOwner->transform.scale *= Vector3(-1.f, 1.f, 1.f);
		_pPannel->transform.scale*= Vector3(-1.f, 1.f, 1.f);
	}
	return 0;
}

int EliteEnemyIdle::LateUpdate(const float& deltaTime)
{
	ShowInfo();
	return (int)_nextState;
}

void EliteEnemyIdle::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");
	Sound::PlaySound("Battle_Sound_Enemy_Common_Wait", (int)SoundGroup::Battle, 0.8f, false);
	//지정한 그리드로 움직이는 메소드
	/*_pMovement->MoveToCell(Vector3(0.f, 0.f, 0.f), 0.5f);
	_pAstar->SetGridPosition(Vector3(0.f, 0.f, 0.f));
	_pAstar->ReCalculatePath();*/
}

void EliteEnemyIdle::OnExit()
{
	CloseInfo();
}

void EliteEnemyIdle::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-30.f, -15.f, 0.f));

	_infoText = L"[None]";
	_pTextRenderer->SetText(_infoText.c_str());
}

void EliteEnemyIdle::CloseInfo()
{
	__super::CloseInfo();
}

EliteEnemy::FSM EliteEnemyIdle::SelectNextBehave()
{
	if (false==_getShield&&_pHP->hp <= 1)
	{
		_getShield = true;
		return EliteEnemy::FSM::GetShield;
	}
	if (CheckRange(3,1))	
	{
		if (_count >= 2)
		{
			_count = 0;
			return EliteEnemy::FSM::WeekSearch;
		}
		if(_pPlayer->GetComponent<Attribute>()->IsActiveState(AttributeFlag::WeakPoint))
		{
			_count++;
			return EliteEnemy::FSM::SuperSlash;
		}
		_count++;
		return EliteEnemy::FSM::NomalAttack;
	}

	if (_pTargetPosition == &(*_ppDefense)->GetGridPosition() &&CheckTower(3, 1))
	{
		_count++;
		return EliteEnemy::FSM::NomalAttack;
	}

	if (!(_pAstar->GetGoalPosition() == *_pGridPosition))
	{
		return EliteEnemy::FSM::Move;
	}
	return EliteEnemy::FSM::None;
}



EliteEnemyIdle* EliteEnemyIdle::Create(EliteEnemyScript* pScript)
{
	EliteEnemyIdle* pInstance = new EliteEnemyIdle;
	pInstance->EliteEnemyState::Initialize(pScript);
	return pInstance;
}
