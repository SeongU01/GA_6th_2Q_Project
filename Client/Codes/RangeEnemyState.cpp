#include "RangeEnemyState.h"
#include "RangeEnemyScript.h"
#include "Astar.h"

#include "TextRenderer.h"
#include "Pannel.h"
#include "GridEffect.h"
#include "Client_Define.h"

void RangeEnemyState::Initialize(RangeEnemyScript* pScript)
{
	if (nullptr == pScript)
		return;

	_pHP = pScript->_pHP;
	_pPlayer = pScript->_pPlayer;
	_pOwner = pScript;
	_pAttribute = pScript->_pAttribute;
	_pSpriteRenderer = pScript->GetComponent<Engine::SpriteRenderer>();
	_pTargetPosition = &(pScript->_targetPosition);
	_pGridPosition = &(pScript->_aStar->_gridPosition);
	_pAnimation = pScript->_pAnimation;
	_pMovement = pScript->_movement;
	_pAstar = pScript->_aStar;
	_pPannel = pScript->_pPannel;
	_pToolTip = pScript->_pToolTip;
	_pTextRenderer = _pPannel->GetComponent<Engine::TextRenderer>();
	_pTextRenderer->SetDrawRect(200.f, 50.f);
	_pGridEffect = Engine::FindObject((int)LayerGroup::UI, L"UI", L"GridEffect")->GetComponent<GridEffect>();
}
