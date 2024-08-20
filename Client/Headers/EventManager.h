#pragma once
#include "GameObject.h"

enum Stage;
class RestartGame;
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
	bool IsStopGame() const { return _isStopGame; }
	bool IsNextStage() const { return _isNextStage; }
	bool IsPlayerDeath() const { return _isPlayerDeath;	}
	bool IsTimeStop() const { return _isTimeStop; }

public:
	void GameOver();

private:
	RestartGame* _pRestartGame = nullptr;
	bool _isStopGame = false;
	bool _isNextStage = false;
	bool _isPlayerDeath = false;
	bool _isTimeStop = false;
};

