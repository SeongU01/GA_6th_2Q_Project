#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class BitFlag;
	class Timer;
}

class AdditiveState : public Engine::MonoBehavior
{
	enum State { Shield, Extra, Charge, HighPower, OverCharge, WeakPoint, End };
public:
	explicit AdditiveState() = default;
private:
	virtual ~AdditiveState() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void AddState(unsigned long long flag);
	bool IsActiveState(unsigned long long flag) const;

private:
	Engine::BitFlag*	_pBitFlag = nullptr;
	Engine::Timer*		_pTimer = nullptr;

	std::vector<float>	_stateDatas[End];
};

