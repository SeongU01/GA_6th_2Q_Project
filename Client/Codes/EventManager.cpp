#include "EventManager.h"

// Component
#include "RestartGame.h"

void EventManager::Initialize()
{
	_pRestartGame = AddComponent<RestartGame>();
}

void EventManager::SetCurrentStage(Stage stage)
{
	_pRestartGame->SetStage(stage);
}

void EventManager::GameOver()
{
	_pRestartGame->GameOver();
}
