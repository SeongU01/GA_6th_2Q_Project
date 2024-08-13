#include "DefaultEnemyState.h"
#include "DefaultEnemyScript.h"
#include "Astar.h"
void DefaultEnemyState::Initialize(DefaultEnemyScript* pScript)
{
	if (nullptr == pScript)
		return;
	_pTargetPosition = &(pScript->_targetPosition);
	_pGridPosition = &(pScript->_aStar->_gridPosition);
	_pOwner = pScript;
	_pAnimation = pScript->_pAnimation;
	_pMovement = pScript->_movement;
	_pAstar = pScript->_aStar;
}
