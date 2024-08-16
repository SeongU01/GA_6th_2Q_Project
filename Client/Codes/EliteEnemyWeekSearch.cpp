#include "EliteEnemyWeekSearch.h"

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
int EliteEnemyWeekSearch::Update(const float& deltaTime)
{
	if (_directionCheck == false)
	{
		if (CheckRange(5, 2))
		{
			_pTargetPosition = &_pPlayer->GetGridPosition();
		}
		else
		{
			_pTargetPosition = &_pDefense->GetGridPosition();
		}
		const Vector3& gridPosition = *_pGridPosition;
		Vector3 Direction = *_pTargetPosition - gridPosition;

		if (_currDirection.x * Direction.x < 0)
		{
			_currDirection.x *= -1;
		}
		_directionCheck = true;
	}

	if (!_isStateOn)
	{
		if (_pAnimation->IsCurrAnimation(L"Idle"))
		{
			_currTime += deltaTime;
		}
		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"Stab");
			//TODO : 공격하기. 피해 1, 허점부여
			_isStateOn = true;
		}

	}
	return 0;
}

int EliteEnemyWeekSearch::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Stab"))
	{
		return (int)EliteEnemy::FSM::Idle;
	}
	return 0;
}

void EliteEnemyWeekSearch::OnStart()
{
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(4, 6);
}

void EliteEnemyWeekSearch::OnExit()
{
}

void EliteEnemyWeekSearch::ShowInfo()
{
	if (_pAnimation->IsCurrAnimation(L"Idle"))
	{
		ShowAttackRange();
	}
	_pTextRenderer->SetOffset(Vector3(-70.f, -15.f, 0.f));
	_pPannel->SetActive(true);
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[WeekFind] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void EliteEnemyWeekSearch::CloseInfo()
{
	_pPannel->SetActive(false);
}

void EliteEnemyWeekSearch::ShowAttackRange()
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

EliteEnemyWeekSearch* EliteEnemyWeekSearch::Create(EliteEnemyScript* pScript)
{
	EliteEnemyWeekSearch* pInstance = new EliteEnemyWeekSearch;
	pInstance->EliteEnemyState::Initialize(pScript);
	return pInstance;
}
