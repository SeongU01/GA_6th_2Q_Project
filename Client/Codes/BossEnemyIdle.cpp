#include "BossEnemyIdle.h"
#include "BossEnemyScript.h"
//component
#include "HP.h"
#include "Astar.h"
#include "Animation.h"
#include "Attribute.h"
#include "Player.h"

#include "TextRenderer.h"
#include "Client_Define.h"

int BossEnemyIdle::Update(const float& deltaTime)
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

	_pTargetPosition = &_pPlayer->GetGridPosition();
	_pAstar->SetGoalPosition(*_pTargetPosition);
	_pAstar->ReCalculatePath();
	Vector3 Direction;
	if (_charge >= 4)
	{
		const Vector3& gridPosition = *_pGridPosition;
		Direction = Vector3(7.f,3.f,0.f) - gridPosition;
	}
	else
	{
		const Vector3& gridPosition = *_pGridPosition;
		Direction = *_pTargetPosition - gridPosition;
	}

	if (_currDirection.x * Direction.x < 0)
	{
		_currDirection.x *= -1;
		_pOwner->transform.scale *= Vector3(-1.f, 1.f, 1.f);
		_pPannel->transform.scale *= Vector3(-1.f, 1.f, 1.f);
	}
	_nextState = SelectNextBehave();
	return 0;
}

int BossEnemyIdle::LateUpdate(const float& deltaTime)
{
	ShowInfo();
	return (int)_nextState;
}

void BossEnemyIdle::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");

}

void BossEnemyIdle::OnExit()
{
	CloseInfo();
}

void BossEnemyIdle::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-30.f, -15.f, 0.f));

	_infoText = L"[None]";
	_pTextRenderer->SetText(_infoText.c_str());
}

void BossEnemyIdle::CloseInfo()
{
	__super::CloseInfo();
}

BossEnemy::FSM BossEnemyIdle::SelectNextBehave()
{
	if (_charge >= 4)
	{
		_charge = 0;
		return BossEnemy::FSM::ReadyMove;
	}
	if (CheckRange(3, 2))
	{
		if (_charge >= 1)
		{
			_charge++;
			if (_pPlayer->GetComponent<Attribute>()->IsActiveState(AttributeFlag::WeakPoint))
			{
				return BossEnemy::FSM::RealMeteorSlash;
			}
			return BossEnemy::FSM::MeteorSlash;
		}
		_charge++;
		return BossEnemy::FSM::SonicStab;
	}
	else
	{
		if (_charge >= 1)
		{
			if (_pHP->hp <= _pHP->GetMaxHP() / 2)
			{
				_charge++;
				return BossEnemy::FSM::RealLaserWave;
			}
			_charge++;
			return BossEnemy::FSM::LaserWave;
		}

		if (!(_pAstar->GetGoalPosition() == *_pGridPosition))
		{
			return BossEnemy::FSM::Move;
		}
	}
	return BossEnemy::FSM::None;
}

BossEnemyIdle* BossEnemyIdle::Create(BossEnemyScript* pScript)
{
	BossEnemyIdle* pInstance = new BossEnemyIdle;
	pInstance->BossEnemyState::Initialize(pScript);
	return pInstance;
}
