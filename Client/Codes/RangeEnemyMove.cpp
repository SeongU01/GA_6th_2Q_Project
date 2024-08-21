#include "RangeEnemyMove.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "TextRenderer.h"
#include "GridMovement.h"

#include "Client_Define.h"
int RangeEnemyMove::Update(const float& deltaTime)
{
	if (!_isStateOn)
	{
		if (_pAnimation->IsCurrAnimation(L"Idle"))
			_currTime += deltaTime;

		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"Move");
			_pAstar->SetMaxMoveSteps(2);
			_isStateOn = true;
		}
	}
	return 0;
}

int RangeEnemyMove::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn)
		ShowInfo();

	if ((_pAstar->GetGoalPosition() == *_pGridPosition))
	{
		_pAstar->ReCalculatePath();
		return (int)RangeEnemy::FSM::Idle;
	}

	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Move"))
		return (int)RangeEnemy::FSM::Idle;
	return 0;
}

void RangeEnemyMove::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(2, 3);
}

void RangeEnemyMove::OnExit()
{
	CloseInfo();
}

void RangeEnemyMove::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Move] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemyMove::CloseInfo()
{
	__super::CloseInfo();
}

RangeEnemyMove* RangeEnemyMove::Create(RangeEnemyScript* pScript)
{
	RangeEnemyMove* pInstance = new RangeEnemyMove;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}
