#include "DefaultEnemyMove.h"
//component
#include "Animation.h"
#include "Astar.h"

int DefaultEnemyMove::Update(const float& deltaTime)
{
	return 0;
}

int DefaultEnemyMove::LateUpdate(const float& deltaTime)
{
	if (_pAstar->CheckMoveEnd())
		return (int)DefaultEnemy::FSM::Idle;
	return 0;
}

void DefaultEnemyMove::OnStart()
{ 
	_pAnimation->ChangeAnimation(L"Move");
	_pAstar->SetMaxMoveSteps(1);
}

void DefaultEnemyMove::OnExit()
{
}

DefaultEnemyMove* DefaultEnemyMove::Create(DefaultEnemyScript* pScript)
{
	DefaultEnemyMove* pInstance = new DefaultEnemyMove;
	pInstance->DefaultEnemyState::Initialize(pScript);
	return pInstance;
}
