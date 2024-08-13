#include "DefaultEnemyIdle.h"

//component
#include "Animation.h"
#include "GridMovement.h"

#include "Client_Define.h"
int DefaultEnemyIdle::Update(const float& deltaTime)
{
	if (_pAnimation->IsLastFrame())
	{
		_pAnimation->ChangeAnimation(L"Idle");
	}
	return 0;
}

int DefaultEnemyIdle::LateUpdate(const float& deltaTime)
{
	_delayTime += deltaTime;

	if (_delayTime >= 2.f)
	{
		_delayTime = 0.f;
		return SelectNextBehave();
	}
	return 0;
}

void DefaultEnemyIdle::OnStart()
{
}

void DefaultEnemyIdle::OnExit()
{
}

int DefaultEnemyIdle::SelectNextBehave()
{
	CheckAttackRange(1);
	
	return (int)DefaultEnemy::FSM::Move;
}

bool DefaultEnemyIdle::CheckAttackRange(int arrange)
{
	_pGridPosition;
	return false;
}

DefaultEnemyIdle* DefaultEnemyIdle::Create(DefaultEnemyScript* pScript)
{
	DefaultEnemyIdle* pInstance = new DefaultEnemyIdle;
	pInstance->DefaultEnemyState::Initialize(pScript);
	return pInstance;
}
