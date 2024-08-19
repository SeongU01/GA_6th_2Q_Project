#include "DefaultEnemyMove.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "Pannel.h"
#include "ToolTip.h"
#include "TextRenderer.h"

#include "Client_Define.h"

std::random_device g_rd;
std::mt19937 g_gen(g_rd());

int DefaultEnemyMove::Update(const float& deltaTime)
{
	if(!_isStateOn)
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

int DefaultEnemyMove::LateUpdate(const float& deltaTime)
{
	if (_isStateOn&&_pAnimation->IsCurrAnimation(L"Move")&&_pAnimation->IsLastFrame())
		return (int)DefaultEnemy::FSM::Idle;
	return 0;
}

void DefaultEnemyMove::OnStart()
{ 
	_isStateOn = false;
	_currTime = 0.f;
	_delayTime = (float)Engine::RandomGeneratorInt(2, 4);
}

void DefaultEnemyMove::OnExit()
{
}

void DefaultEnemyMove::ShowInfo()
{
	__super::ShowInfo();
	_pTextRenderer->SetOffset(Vector3(-50.f, -15.f, 0.f));
	std::wstringstream wss;
	wss << std::fixed << std::setprecision(1) << (_delayTime - _currTime);
	std::wstring timeString = wss.str();

	_infoText = L"[Move] " + timeString+L" s";
	_pTextRenderer->SetText(_infoText.c_str());
}

void DefaultEnemyMove::CloseInfo()
{
	__super::CloseInfo();
}

DefaultEnemyMove* DefaultEnemyMove::Create(DefaultEnemyScript* pScript)
{
	DefaultEnemyMove* pInstance = new DefaultEnemyMove;
	pInstance->DefaultEnemyState::Initialize(pScript);
	return pInstance;
}
