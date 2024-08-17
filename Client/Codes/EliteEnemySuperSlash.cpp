#include "EliteEnemySuperSlash.h"

#include "EliteEnemyScript.h"
//component
#include "Animation.h"
#include "TextRenderer.h"
#include "GridEffect.h"
#include "Player.h"
#include "DefenseScript.h"

#include "DataManager.h"
#include "Client_Define.h"
int EliteEnemySuperSlash::Update(const float& deltaTime)
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
			_pAnimation->ChangeAnimation(L"Attack");
			//TODO : 공격하기. 피해 1
			_isStateOn = true;
		}

	}
	return 0;
}

int EliteEnemySuperSlash::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Attack"))
	{
		return (int)EliteEnemy::FSM::Idle;
	}
	return 0;
}

void EliteEnemySuperSlash::OnStart()
{
	_directionCheck = false;
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(3, 5);
}

void EliteEnemySuperSlash::OnExit()
{
}

void EliteEnemySuperSlash::ShowInfo()
{
	__super::ShowInfo();
	if (_pAnimation->IsCurrAnimation(L"Idle"))
	{
		ShowAttackRange();
	}
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Attack] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void EliteEnemySuperSlash::CloseInfo()
{
	__super::CloseInfo();
}

void EliteEnemySuperSlash::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(15);
	int index = 1;

	for (auto& grid : ranges)
	{
		if (_currDirection.x >= 0)
			_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), index);
		else
			_pGridEffect->OnEffect(int(gridPosition.x - grid.first), int(gridPosition.y + grid.second), index);

	}
}

EliteEnemySuperSlash* EliteEnemySuperSlash::Create(EliteEnemyScript* pScript)
{
	EliteEnemySuperSlash* pInstance = new EliteEnemySuperSlash;
	pInstance->EliteEnemyState::Initialize(pScript);
	return pInstance;
}
