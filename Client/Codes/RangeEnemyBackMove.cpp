#pragma once
#include "RangeEnemyBackMove.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "Pannel.h"
#include "TextRenderer.h"

#include "Client_Define.h"

int RangeEnemyBackMove::Update(const float& deltaTime)
{
	if (!_isStateOn)
	{
		if (_pAnimation->IsCurrAnimation(L"Idle"))
			_currTime += deltaTime;

		if (_currTime >= _delayTime)
		{
			_currTime = _delayTime;
			_pAnimation->ChangeAnimation(L"Move");
			_pAstar->SetMaxMoveSteps(1);
			_isStateOn = true;
		}
	}
	return 0;
}

int RangeEnemyBackMove::LateUpdate(const float& deltaTime)
{
	if (_isStateOn && _pAnimation->IsCurrAnimation(L"Move") && _pAnimation->IsLastFrame())
		return (int)RangeEnemy::FSM::Idle;
	return 0;
}

void RangeEnemyBackMove::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(3, 5);
}

void RangeEnemyBackMove::OnExit()
{
}

void RangeEnemyBackMove::ShowInfo()
{
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	_pPannel->SetActive(true);
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Move] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void RangeEnemyBackMove::CloseInfo()
{
	_pPannel->SetActive(false);
}

RangeEnemyBackMove* RangeEnemyBackMove::Create(RangeEnemyScript* pScript)
{
	RangeEnemyBackMove* pInstance = new RangeEnemyBackMove;
	pInstance->RangeEnemyState::Initialize(pScript);
	return pInstance;
}
