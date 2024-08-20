#include "DefaultEnemyIdle.h"

//component
#include "Animation.h"
#include "GridMovement.h"
#include "DefaultEnemyScript.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "Astar.h"
#include "SpriteRenderer.h"
#include "HP.h"

#include "Client_Define.h"



int DefaultEnemyIdle::Update(const float& deltaTime)
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

	const Vector3& gridPosition = *_pGridPosition;
	Vector3 Direction = *_pTargetPosition - gridPosition;

	if (_currDirection.x * Direction.x < 0)
	{
		_currDirection.x *= -1;
		_pOwner->transform.scale *= Vector3(-1.f, 1.f, 1.f);
		_pPannel->transform.scale *= Vector3(-1.f, 1.f, 1.f);
	}
	return 0;
}

int DefaultEnemyIdle::LateUpdate(const float& deltaTime)
{
	ShowInfo();
	return (int)_nextState;
}

void DefaultEnemyIdle::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");
}

void DefaultEnemyIdle::OnExit()
{
	CloseInfo();
}

void DefaultEnemyIdle::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-30.f, -15.f, 0.f));

	_infoText = L"[None]";
	_pTextRenderer->SetText(_infoText.c_str());
}

void DefaultEnemyIdle::CloseInfo()
{
	__super::CloseInfo();
}

DefaultEnemy::FSM DefaultEnemyIdle::SelectNextBehave()
{
	if (CheckAttackRange(1, 1))
	{
		if (_chargeStack < 2)
		{
			_chargeStack++;
			return DefaultEnemy::FSM::WeakAttack;
		}
		else if (_chargeStack >= 2)
		{
			_chargeStack = 0;
			return DefaultEnemy::FSM::StrongAttack;
		}
	}
	if (!(_pAstar->GetGoalPosition() == *_pGridPosition))
	{
		return DefaultEnemy::FSM::Move;
	}
	return DefaultEnemy::FSM::None;
}

bool DefaultEnemyIdle::CheckAttackRange(int x,int y)
{
	Vector3 currPosition = *_pGridPosition;

	int currGridX =(int)currPosition.x;
	int currGridY =(int)currPosition.y;
	
	for (int dx = -x; dx <= x; dx++)
	{
		for (int dy = -y; dy <= y; dy++)
		{
			Vector3 temp = { (float)(currGridX + dx),(float)(currGridY + dy),0.f };
			if (temp == *_pTargetPosition)
			{
				return true;
			}
		}
	}
	return false;
}

DefaultEnemyIdle* DefaultEnemyIdle::Create(DefaultEnemyScript* pScript)
{
	DefaultEnemyIdle* pInstance = new DefaultEnemyIdle;
	pInstance->DefaultEnemyState::Initialize(pScript);
	return pInstance;
}
