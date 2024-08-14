#include "RangeEnemyIdle.h"

//component
#include "Animation.h"
#include "GridMovement.h"

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
	if (CheckAttackRange(1, 1))
	{
		if (_chargeStack < 2)
		{
			_chargeStack++;
			return RangeEnemy::FSM::Attack;
		}
		else if (_chargeStack >= 2)
		{
			_chargeStack = 0;
			return RangeEnemy::FSM::Attack;
		}
	}

	return RangeEnemy::FSM::ForwardMove;
}

bool RangeEnemyIdle::CheckAttackRange(int x, int y)
{
	Vector3 currPosition = *_pGridPosition;

	int currGridX = (int)currPosition.x;
	int currGridY = (int)currPosition.y;

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

RangeEnemyIdle* RangeEnemyIdle::Create(RangeEnemyScript* pScript)
{
	RangeEnemyIdle* pInstance = new RangeEnemyIdle;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}