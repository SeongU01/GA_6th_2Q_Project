#include "EventManager.h"

// Component
#include "RestartGame.h"
#include "Operator.h"

void EventManager::Initialize()
{
	_pRestartGame = AddComponent<RestartGame>();
	_pOperator = AddComponent<Operator>();
}

void EventManager::SetCurrentStage(Stage stage)
{
	_pRestartGame->SetStage(stage);
}

void EventManager::GameOver()
{
	_pRestartGame->GameOver();
}

void EventManager::Tutorial1()
{
	if(_pOperator->Tutorial1())
		_isTutorial = true;
}

bool EventManager::Tutorial2()
{
	if (_pOperator->Tutorial2())
	{
		_isTutorial = true;
		return true;
	}

	return false;
}

bool EventManager::Tutorial3()
{
	if (_pOperator->Tutorial3())
	{
		_isTutorial = true;
		return true;
	}

	return false;
}
