#include "EliteEnemyIdle.h"

//component
#include "Animation.h"
#include "GridMovement.h"

#include "Client_Define.h"

int EliteEnemyIdle::Update(const float& deltaTime)
{
	return 0;
}

int EliteEnemyIdle::LateUpdate(const float& deltaTime)
{
	return (int)SelectNextBehave();
}

void EliteEnemyIdle::OnStart()
{
	_pAnimation->ChangeAnimation(L"Idle");
}

void EliteEnemyIdle::OnExit()
{
}

EliteEnemy::FSM EliteEnemyIdle::SelectNextBehave()
{
	return EliteEnemy::FSM::Move;
}

bool EliteEnemyIdle::CheckAttackRange(int x, int y)
{
	return false;
}

EliteEnemyIdle* EliteEnemyIdle::Create(EliteEnemyScript* pScript)
{
	EliteEnemyIdle* pInstance = new EliteEnemyIdle;
	pInstance->EliteEnemyState::Initialize(pScript);
	return pInstance;
}
