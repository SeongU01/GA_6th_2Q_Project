#include "EliteEnemyMove.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "TextRenderer.h"
#include "GridMovement.h"

#include "Client_Define.h"
int EliteEnemyMove::Update(const float& deltaTime)
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

int EliteEnemyMove::LateUpdate(const float& deltaTime)
{
	if (!_isStateOn)
		ShowInfo();

	if (_isStateOn && _pAnimation->IsLastFrame() && _pAnimation->IsCurrAnimation(L"Move"))
		return (int)EliteEnemy::FSM::Idle;
	return 0;
}

void EliteEnemyMove::OnStart()
{
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(3, 5);
}

void EliteEnemyMove::OnExit()
{
	CloseInfo();
}

void EliteEnemyMove::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Move] " + timeString + L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void EliteEnemyMove::CloseInfo()
{
	__super::CloseInfo();
}

EliteEnemyMove* EliteEnemyMove::Create(EliteEnemyScript* pScript)
{
	EliteEnemyMove* pInstance = new EliteEnemyMove;
	pInstance->EliteEnemyState::Initialize(pScript);
	return pInstance;
}
