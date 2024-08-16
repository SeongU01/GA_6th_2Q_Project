#include "EliteMonsterWeekSearch.h"

#include "EliteEnemyScript.h"
//component
#include "Animation.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "GridEffect.h"
#include "Player.h"
#include "DefenseScript.h"

#include "DataManager.h"
#include "Client_Define.h"
int EliteMonsterWeekSearch::Update(const float& deltaTime)
{

    return 0;
}

int EliteMonsterWeekSearch::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Stab"))
	{
		return (int)EliteEnemy::FSM::Idle;
	}
	return 0;
}

void EliteMonsterWeekSearch::OnStart()
{
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(4, 6);
}

void EliteMonsterWeekSearch::OnExit()	
{
}

void EliteMonsterWeekSearch::ShowInfo()
{
	if (_pAnimation->IsCurrAnimation(L"Idle"))
	{
		ShowAttackRange();
	}
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	_pPannel->SetActive(true);
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[WeeknessFind] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void EliteMonsterWeekSearch::CloseInfo()
{
	_pPannel->SetActive(false);
}

void EliteMonsterWeekSearch::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(16);
	int index = 1;

	for (auto& grid : ranges)
	{
		if (_currDirection.x >= 0)
			_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), index);
		else
			_pGridEffect->OnEffect(int(gridPosition.x - grid.first), int(gridPosition.y + grid.second), index);

	}
}

EliteMonsterWeekSearch* EliteMonsterWeekSearch::Create(EliteEnemyScript* pScript)
{
  EliteMonsterWeekSearch* pInstance = new EliteMonsterWeekSearch;
  pInstance->EliteEnemyState::Initialize(pScript);
  return pInstance;
}
