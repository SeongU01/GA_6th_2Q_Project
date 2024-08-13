#include "DefaultEnemyIdle.h"

//component
#include "Animation.h"
#include "GridMovement.h"

#include "Client_Define.h"



int DefaultEnemyIdle::Update(const float& deltaTime)
{
	

	return 0;
}

int DefaultEnemyIdle::LateUpdate(const float& deltaTime)
{
	
	return (int)SelectNextBehave();
}

void DefaultEnemyIdle::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");
}

void DefaultEnemyIdle::OnExit()
{
}

DefaultEnemy::FSM DefaultEnemyIdle::SelectNextBehave()
{
	if (CheckAttackRange(1, 1))
	{
		return DefaultEnemy::FSM::WeakAttack;
	}
	
	return DefaultEnemy::FSM::Move;
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
