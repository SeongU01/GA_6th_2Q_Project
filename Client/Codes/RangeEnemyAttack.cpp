#include "RangeEnemyAttack.h"
//component
#include "Animation.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "GridEffect.h"

#include "DataManager.h"
#include "Client_Define.h"
int RangeEnemyAttack::Update(const float& deltaTime)
{
	if (!_isStateOn)
	{
		if (_pAnimation->IsCurrAnimation(L"Idle"))
			_currTime += deltaTime;

		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"Attack");
			_isStateOn = true;
		}
	}
	return 0;
}

int RangeEnemyAttack::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsCurrAnimation(L"Attack") && _pAnimation->IsLastFrame())
		return (int)RangeEnemy::FSM::Idle;
	return 0;
}

void RangeEnemyAttack::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(3, 5);
}

void RangeEnemyAttack::OnExit()
{
}

void RangeEnemyAttack::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(12);
	int index = 1;
	for (auto& grid : ranges)
	{
		_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), index);
	}
}


void RangeEnemyAttack::ShowInfo()
{
	if (_pAnimation->IsCurrAnimation(L"Idle"))
	{
		ShowAttackRange();
	}

	_pTextRenderer->SetOffset(Vector3(-60.f, -15.f, 0.f));
	_pPannel->SetActive(true);
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Attack] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemyAttack::CloseInfo()
{
	_pPannel->SetActive(false);
}

RangeEnemyAttack* RangeEnemyAttack::Create(RangeEnemyScript* pScript)
{
	RangeEnemyAttack* pInstance = new RangeEnemyAttack;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}
