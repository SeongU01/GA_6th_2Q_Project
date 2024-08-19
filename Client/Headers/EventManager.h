#pragma once
#include "Base.h"

class EventManager : public Engine::Base, public Engine::SingleTon<EventManager>
{
	friend class SingleTon;
private:
	explicit EventManager() = default;
	virtual ~EventManager() = default;
	NOCOPY(EventManager);

public:
	void SetStageClear(bool isClear) { _isStageClear = isClear; }
	void SetNextStage(bool isNext) { _isNextStage = isNext; }
	bool IsStageClear() const { return _isStageClear; }
	bool IsNextStage() const { return _isNextStage; }

private:
	void Free() override;

private:
	bool _isStageClear = false;
	bool _isNextStage = false;
};

