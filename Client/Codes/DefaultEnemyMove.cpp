#include "DefaultEnemyMove.h"
//component
#include "Animation.h"
#include "Astar.h"
#include "Pannel.h"
#include "TextRenderer.h"

#include "Client_Define.h"

std::random_device g_rd;
std::mt19937 g_gen(g_rd());

int DefaultEnemyMove::Update(const float& deltaTime)
{
	return 0;
}

int DefaultEnemyMove::LateUpdate(const float& deltaTime)
{
	_currTime += deltaTime;

	if (_currTime >= _delayTime)
	{
		_currTime = 0.f;
		_pAnimation->ChangeAnimation(L"Move");
		_pAstar->SetMaxMoveSteps(1);
	}

	if (_pAnimation->IsLastFrame())
		return (int)DefaultEnemy::FSM::Idle;
	return 0;
}

void DefaultEnemyMove::OnStart()
{ 
	_delayTime = (float)Engine::RandomGeneratorInt(3, 5);
}

void DefaultEnemyMove::OnExit()
{
}

void DefaultEnemyMove::ShowInfo()
{
	_pPannel->SetActive(true);
	_infoText = L"Move : " + std::to_wstring(_delayTime-_currTime);
	_pTextRenderer->SetText(_infoText.c_str());
}

void DefaultEnemyMove::CloseInfo()
{
	_pPannel->SetActive(false);
}

DefaultEnemyMove* DefaultEnemyMove::Create(DefaultEnemyScript* pScript)
{
	DefaultEnemyMove* pInstance = new DefaultEnemyMove;
	pInstance->DefaultEnemyState::Initialize(pScript);
	return pInstance;
}
