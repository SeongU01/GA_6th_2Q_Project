#pragma once
#include "GameObject.h"

enum Stage;
class RestartGame;
class Operator;
class EventManager : public Engine::GameObject, public Engine::SingleTon<EventManager>
{
	friend class SingleTon;
private:
	explicit EventManager() = default;
	virtual ~EventManager() = default;
	NOCOPY(EventManager);

public:
	void Initialize();
	void SetStopGame(bool isClear) { _isStopGame = isClear; }
	void SetNextStage(bool isNext) { _isNextStage = isNext; }
	void SetPlayerDeath(bool isDeath) { _isPlayerDeath = isDeath; }
	void SetTimeStop(bool isStop) { _isTimeStop = isStop; }
	void SetCurrentStage(Stage stage);
	void SetActiveTutorial(bool isActive) { _isTutorial = isActive; }
	bool IsStopGame() const { return _isStopGame; }
	bool IsNextStage() const { return _isNextStage; }
	bool IsPlayerDeath() const { return _isPlayerDeath;	}
	bool IsTimeStop() const { return _isTimeStop; }
	bool IsTutorial() const { return _isTutorial; }

public:
	void GameOver();
	void Tutorial1();
	bool Tutorial2();
	bool Tutorial3();

private:
	Operator* _pOperator = nullptr;
	RestartGame* _pRestartGame = nullptr;
	bool _isStopGame = false;
	bool _isNextStage = false;
	bool _isPlayerDeath = false;
	bool _isTimeStop = false;
	bool _isTutorial = false;
};

