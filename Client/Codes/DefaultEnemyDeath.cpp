#include "DefaultEnemyDeath.h"
//component
#include "Animation.h"
#include "GridMovement.h"
#include "Tile.h"
#include "Grid.h"
#include "HPHUD.h"
#include "AttributeHUD.h"
#include "Pannel.h"

#include "Client_Define.h"
#include "DefaultEnemyScript.h"
int DefaultEnemyDeath::Update(const float& deltaTime)
{
	return 0;
}

int DefaultEnemyDeath::LateUpdate(const float& deltaTime)
{
	if (_pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Death"))
	{
		std::string str = "Voice_Sound_Voice_Zero_Kill" + std::to_string(Engine::RandomGeneratorInt(1, 4));
		Sound::StopSound((int)SoundGroup::Voice);
		Sound::PlaySound(str.c_str(), (int)SoundGroup::Voice, 0.8f, false);
		Sound::PlaySound("Battle_Sound_Enemy_Common_Dead", (int)SoundGroup::Battle, 0.8f, false);

		_pOwner->GetComponent<HPHUD>()->DeleteUI();
		_pOwner->GetComponent<AttributeHUD>()->DeleteUI();
		_pPannel->SetDead();
		_pMovement->_grid->GetTiles()[(int)_pGridPosition->y][(int)_pGridPosition->x]->canMove = true;
		_pOwner->gameObject.SetDead();
	}
	return 0;
}

void DefaultEnemyDeath::OnStart()
{
	
	_pAnimation->ChangeAnimation(L"Death");
}

void DefaultEnemyDeath::OnExit()
{
}

DefaultEnemyDeath* DefaultEnemyDeath::Create(DefaultEnemyScript* pScript)
{
	DefaultEnemyDeath* pInstance = new DefaultEnemyDeath;
	pInstance->DefaultEnemyState::Initialize(pScript);
	return pInstance;
}
