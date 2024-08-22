#include "RangeEnemyDeath.h"
#include "RangeEnemyScript.h"
//component
#include "Animation.h"
#include "GridMovement.h"
#include "Tile.h"
#include "Grid.h"
#include "HPHUD.h"
#include "AttributeHUD.h"
#include "Collider.h"

#include "Client_Define.h"
int RangeEnemyDeath::Update(const float& deltaTime)
{
    return 0;
}

int RangeEnemyDeath::LateUpdate(const float& deltaTime)
{
	if (_pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Death"))
	{
		_pToolTip->RemoveAllToolTip();
		_pOwner->GetComponent<HPHUD>()->DeleteUI();
		_pOwner->GetComponent<AttributeHUD>()->DeleteUI();
		_pOwner->GetComponent<AttributeHUD>()->RemoveAllToolTip();
		_pPannel->SetDead();
		_pMovement->_grid->GetTiles()[(int)_pGridPosition->y][(int)_pGridPosition->x]->canMove = true;
		Sound::PlaySound("Battle_Sound_Enemy_Common_Dead", (int)SoundGroup::Battle);
		_pOwner->gameObject.SetDead();
	}
	return 0;
}

void RangeEnemyDeath::OnStart()
{
	_pOwner->GetComponent<Engine::Collider>()->SetActive(false);
}

void RangeEnemyDeath::OnExit()
{
  _pAnimation->ChangeAnimation(L"Death");
}

RangeEnemyDeath* RangeEnemyDeath::Create(RangeEnemyScript* pScript)
{
  RangeEnemyDeath* pInstance = new RangeEnemyDeath;
  pInstance->RangeEnemyState::Initialize(pScript);
  return pInstance;
}
