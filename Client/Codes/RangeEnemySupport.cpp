#include "RangeEnemySupport.h"
//component
#include "Animation.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "GridEffect.h"

#include "DataManager.h"
#include "Client_Define.h"
int RangeEnemySupport::Update(const float& deltaTime)
{
	if (!_isStateOn)
	{
		//if (_pAnimation->IsCurrAnimation(L"Idle"))
			_currTime += deltaTime;

		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"Charge");
			_isStateOn = true;
		}
	}
	return 0;
}

int RangeEnemySupport::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsCurrAnimation(L"Charge") && _pAnimation->IsLastFrame())
	{
		if (CheckAttackRange(4, 2))
			return (int)RangeEnemy::FSM::Attack; //공격
		return (int)RangeEnemy::FSM::Support; //계속대기..
	}
	return 0;
}

void RangeEnemySupport::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = 1.0f;
}

void RangeEnemySupport::OnExit()
{
}

void RangeEnemySupport::ShowAttackRange()
{
	const Vector3& gridPosition = *_pGridPosition;
	std::vector<std::pair<int, int>> ranges = DataManager::GetInstance()->GetAttackRange(13);
	int index = 1;
	for (auto& grid : ranges)
	{

		_pGridEffect->OnEffect(int(gridPosition.x + grid.first), int(gridPosition.y + grid.second), index);
	}
}


bool RangeEnemySupport::CheckAttackRange(int x, int y)
{
	Vector3 currPosition = *_pGridPosition;

	int currGridX = (int)currPosition.x;
	int currGridY = (int)currPosition.y;
	if (abs(currGridX - _pTargetPosition->x) <= x &&
		abs(currGridY - _pTargetPosition->y) <= y)
	{
		return true;
	}
	return false;
}

void RangeEnemySupport::ShowInfo()
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

	_infoText = L"[Charge] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemySupport::CloseInfo()
{
	_pPannel->SetActive(false);
}

RangeEnemySupport* RangeEnemySupport::Create(RangeEnemyScript* pScript)
{
	RangeEnemySupport* pInstance = new RangeEnemySupport;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}
