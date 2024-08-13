#include "DefaultEnemyState.h"
#include "DefaultEnemyScript.h"
#include "Astar.h"

#include "TextRenderer.h"
#include "Pannel.h"

#include "Client_Define.h"

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
	_pPannel = pScript->_pPannel;
	_pTextRenderer = _pPannel->GetComponent<Engine::TextRenderer>();
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	_pTextRenderer->SetDrawRect(100.f, 50.f);
}
