#include "BossEnemyState.h"
#include "BossEnemyScript.h"
#include "Astar.h"
#include "Grid.h"

#include "Animation.h"
#include "HP.h"
#include "DefenseScript.h"
#include "Player.h"
#include "TextRenderer.h"
#include "Pannel.h"
#include "GridEffect.h"
#include "Client_Define.h"


void BossEnemyState::Initialize(BossEnemyScript* pScript)
{
	if (nullptr == pScript)
		return;

	_pAttribute = pScript->_pAttribute;
	_pSpriteRenderer = pScript->GetComponent<Engine::SpriteRenderer>();
	_pHP = pScript->_pHP;
	_pPlayer = pScript->_pPlayer;
	_pTargetPosition = &(pScript->_targetPosition);
	_pGridPosition = &(pScript->_aStar->_gridPosition);
	_pOwner = pScript;
	_pAnimation = pScript->_pAnimation;
	_pMovement = pScript->_movement;
	_pAstar = pScript->_aStar;
	_pPannel = pScript->_pPannel;
	_pToolTip = pScript->_pToolTip;
	_pTextRenderer = _pPannel->GetComponent<Engine::TextRenderer>();
	_pTextRenderer->SetDrawRect(200.f, 50.f);
	_pGridEffect = Engine::FindObject((int)LayerGroup::UI, L"UI", L"GridEffect")->GetComponent<GridEffect>();

}
bool BossEnemyState::CheckRange(int x, int y)
{
	Vector3 currPosition = *_pGridPosition;

	int currGridX = (int)currPosition.x;
	int currGridY = (int)currPosition.y;

	for (int dx = -x; dx <= x; dx++)
	{
		for (int dy = -y; dy <= y; dy++)
		{
			Vector3 temp = { (float)(currGridX + dx),(float)(currGridY + dy),0.f };
			if (temp == _pPlayer->GetGridPosition())
			{
				return true;
			}
		}
	}
	return false;
}