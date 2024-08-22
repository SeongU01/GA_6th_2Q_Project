#include "BossEnemyDeath.h"
//component
#include "Animation.h"
#include "GridMovement.h"
#include "Tile.h"
#include "Grid.h"
#include "HPHUD.h"
#include "AttributeHUD.h"
#include "Collider.h"
#include "TopHUD.h"

#include "Client_Define.h"
#include "BossEnemyScript.h"
int BossEnemyDeath::Update(const float& deltaTime)
{
	return 0;
}

int BossEnemyDeath::LateUpdate(const float& deltaTime)
{
	if (_pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Death"))
	{
		_pToolTip->RemoveAllToolTip();
		_pOwner->GetComponent<HPHUD>()->DeleteUI();
		_pOwner->GetComponent<AttributeHUD>()->RemoveAllToolTip();
		_pOwner->GetComponent<AttributeHUD>()->DeleteUI();
		_pPannel->SetDead();
		_pMovement->_grid->GetTiles()[(int)_pGridPosition->y][(int)_pGridPosition->x]->canMove = true;
		_pOwner->gameObject.SetDead();
	}
	return 0;
}

void BossEnemyDeath::OnStart()
{
	_pOwner->GetComponent<Engine::Collider>()->SetActive(false);
	_pAnimation->ChangeAnimation(L"Death");
	std::string str = "Voice_Sound_Voice_First_HP_0_" + std::to_string(Engine::RandomGeneratorInt(1, 3));
	Sound::PlaySound(str.c_str(), (int)SoundGroup::FirstEnemy,1.0f,false);
}

void BossEnemyDeath::OnExit()
{
}

BossEnemyDeath* BossEnemyDeath::Create(BossEnemyScript* pScript)
{
	BossEnemyDeath* pInstance = new BossEnemyDeath;
	pInstance->BossEnemyState::Initialize(pScript);
	return pInstance;
}
