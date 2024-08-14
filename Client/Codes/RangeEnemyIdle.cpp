#include "RangeEnemyIdle.h"

//component
#include "Animation.h"
#include "GridMovement.h"
#include "Astar.h"
#include "Client_Define.h"



int RangeEnemyIdle::Update(const float& deltaTime)
{
	return 0;
}

int RangeEnemyIdle::LateUpdate(const float& deltaTime)
{

	return (int)SelectNextBehave();
}

void RangeEnemyIdle::OnStart()
{
	
	_pAnimation->ChangeAnimation(L"Idle");
}

void RangeEnemyIdle::OnExit()
{
}

RangeEnemy::FSM RangeEnemyIdle::SelectNextBehave()
{
	_pAstar->SetGoalPosition(*_pTargetPosition);
	if (_chargeStack == 2) //충전완료
	{
		_chargeStack = 0;
		_isBack = false;
		return RangeEnemy::FSM::Support;
	}
	else
	{
		_chargeStack++;
		if (CheckAttackRange(2, 2)&& !_isBack)//범위안에있다
		{
			_isBack = true;
			return RangeEnemy::FSM::BackMove;
		}
		_isBack = false;
		return RangeEnemy::FSM::ForwardMove;
	}
}

bool RangeEnemyIdle::CheckAttackRange(int x, int y)
{
	Vector3 currPosition = *_pGridPosition;

	int currGridX = (int)currPosition.x;
	int currGridY = (int)currPosition.y;
	if (abs(currGridX - _pTargetPosition->x) <= x &&
		abs(currGridY - _pTargetPosition->y) <= y)
	{
		return true;
	}
	return false;
}

RangeEnemyIdle* RangeEnemyIdle::Create(RangeEnemyScript* pScript)
{
	RangeEnemyIdle* pInstance = new RangeEnemyIdle;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}