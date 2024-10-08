#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class BitFlag;
	class Timer;
}

class Attribute : public Engine::MonoBehavior
{
public:
	enum State { Shield, Extra, Charge, HighPower, OverCharge, WeakPoint, End };
public:
	explicit Attribute();
private:
	virtual ~Attribute() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	int GetExtraRecoveryValue() const;
	bool IsActiveState(unsigned long long flag) const;
	void UseStack(State state);
	int ActiveWeakPoint();
	void ActiveCharge();
	int ActiveHighPower();
	void AddState(unsigned long long flag, int stack);
	void Reset();
	int GetStack(int index) const { return _stateStacks[index]; }

private:
	Engine::BitFlag*			_pBitFlag = nullptr;
	Engine::Timer*				_pTimer = nullptr;
	std::vector<float>			_stateDatas[State::End];
	int							_stateStacks[State::End]{};
};

