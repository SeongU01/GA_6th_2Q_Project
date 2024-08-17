#pragma once
#include "RangeEnemyForwardMove.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "TextRenderer.h"

#include "Client_Define.h"

int RangeEnemyForwardMove::Update(const float& deltaTime)
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

int RangeEnemyForwardMove::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsCurrAnimation(L"Move") && _pAnimation->IsLastFrame())
		return (int)RangeEnemy::FSM::Idle;
	return 0;
}

void RangeEnemyForwardMove::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(1, 3);
}

void RangeEnemyForwardMove::OnExit()
{
}

void RangeEnemyForwardMove::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Move] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemyForwardMove::CloseInfo()
{
	__super::CloseInfo();;
}

RangeEnemyForwardMove* RangeEnemyForwardMove::Create(RangeEnemyScript* pScript)
{
	RangeEnemyForwardMove* pInstance = new RangeEnemyForwardMove;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}
