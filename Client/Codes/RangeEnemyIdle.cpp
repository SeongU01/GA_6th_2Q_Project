#include "RangeEnemyIdle.h"
#include "RangeEnemyScript.h"
//component
#include "HP.h"
#include "Astar.h"
#include "Animation.h"
#include "Attribute.h"
#include "Player.h"

#include "TextRenderer.h"
#include "Client_Define.h"




int RangeEnemyIdle::Update(const float& deltaTime)
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
			_pHP->SetInvinsibleTime(0.2f);
			_pHP->SetInvinsible(false);
			_isFandIn = true;
		}
		return 0;
	}

	_pTargetPosition = &_pPlayer->GetGridPosition();
	_pAstar->SetGoalPosition(*_pTargetPosition);
	_pAstar->ReCalculatePath();
	Vector3 Direction;

	const Vector3& gridPosition = *_pGridPosition;
	Direction = _pPlayer->GetGridPosition() - gridPosition;
	

	if (_currDirection.x * Direction.x < 0)
	{
		_currDirection.x *= -1;
		_pOwner->transform.scale *= Vector3(-1.f, 1.f, 1.f);
		_pPannel->transform.scale *= Vector3(-1.f, 1.f, 1.f);
	}
	_nextState = SelectNextBehave();
	return 0;
}

int RangeEnemyIdle::LateUpdate(const float& deltaTime)
{
	return (int)_nextState;
}

void RangeEnemyIdle::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");
	Sound::PlaySound("Battle_Sound_Enemy_Common_Wait", (int)SoundGroup::Battle, 0.8f, false);
}

void RangeEnemyIdle::OnExit()
{
	CloseInfo();
}

void RangeEnemyIdle::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-30.f, -15.f, 0.f));

	_infoText = L"[None]";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemyIdle::CloseInfo()
{
	__super::CloseInfo();
}

RangeEnemy::FSM RangeEnemyIdle::SelectNextBehave()
{
	if (CheckTargetRange(2, 1))
	{
		return RangeEnemy::FSM::Attack;
	}
	if (!(_pAstar->GetGoalPosition() == *_pGridPosition))
	{
		return RangeEnemy::FSM::Move;
	}
	return RangeEnemy::FSM::None;
}

bool RangeEnemyIdle::CheckTargetRange(int x, int y)
{
	Vector3 currPosition = *_pGridPosition;

	int currGridX = (int)currPosition.x;
	int currGridY = (int)currPosition.y;

	for (int dx = -x; dx <= x; dx++)
	{
		for (int dy = -y; dy <= y; dy++)
		{
			Vector3 temp = { (float)(currGridX + dx),(float)(currGridY + dy),0.f };
			if (temp == _pPlayer->GetGridPosition())
			{
				return true;
			}
		}
	}
	return false;
}

RangeEnemyIdle* RangeEnemyIdle::Create(RangeEnemyScript* pScript)
{
	RangeEnemyIdle* pInstance = new RangeEnemyIdle;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}