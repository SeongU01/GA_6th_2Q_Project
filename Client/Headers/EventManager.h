#pragma once
#include "GameObject.h"

class EventManager : public Engine::GameObject, public Engine::SingleTon<EventManager>
{
	friend class SingleTon;
private:
	explicit EventManager() = default;
	virtual ~EventManager() = default;
	NOCOPY(EventManager);

public:
	void SetStopGame(bool isClear) { _isStopGame = isClear; }
	void SetNextStage(bool isNext) { _isNextStage = isNext; }
	void SetPlayerDeath(bool isDeath) { _isPlayerDeath = isDeath; }
	bool IsStopGame() const { return _isStopGame; }
	bool IsNextStage() const { return _isNextStage; }
	bool IsPlayerDeath() const { return _isPlayerDeath;	}

private:
	bool _isStopGame = false;
	bool _isNextStage = false;
	bool _isPlayerDeath = false;
};

