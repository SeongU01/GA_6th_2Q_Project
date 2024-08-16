#include "EliteEnemyDeath.h"
//component
#include "Animation.h"
#include "GridMovement.h"
#include "Tile.h"
#include "Grid.h"

#include "Client_Define.h"
#include "EliteEnemyScript.h"
int EliteEnemyDeath::Update(const float& deltaTime)
{
	return 0;
}

int EliteEnemyDeath::LateUpdate(const float& deltaTime)
{
	if (_pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Death"))
	{
		_pMovement->_grid->GetTiles()[(int)_pGridPosition->y][(int)_pGridPosition->x]->canMove = true;
		_pOwner->gameObject.SetDead();
	}
	return 0;
}

void EliteEnemyDeath::OnStart()
{
	_pAnimation->ChangeAnimation(L"Death");
}

void EliteEnemyDeath::OnExit()
{
}

EliteEnemyDeath* EliteEnemyDeath::Create(EliteEnemyScript* pScript)
{
	EliteEnemyDeath* pInstance = new EliteEnemyDeath;
	pInstance->EliteEnemyState::Initialize(pScript);
	return pInstance;
}
