#pragma once
#include "MonoBehavior.h"

class HP :public Engine::MonoBehavior
{
public:
	explicit HP(const wchar_t* name, int maxHp);
private:
	virtual ~HP() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	int GetHP() { return _HP; }
	void SetHP(int hp) 
	{
		_HP = hp; 
		_isInvinsible = true;
	}
	__declspec(property(get = GetHP, put = SetHP))int hp;

	const int GetMaxHP() { return _maxHP; }
	void SetInvinsible(bool _invinsible) { _isInvinsible = _invinsible;}
	void SetInvinsibleTime(float _time) { _invinsibleDuration = _time;}
	bool IsZeroHP() { return 0 >= _HP; }
	bool IsInvinsible() { return _isInvinsible; }
private:
	int _HP = 0;
	int _maxHP = 0;
	bool _isInvinsible = false;
	float _invinsibleDuration = 1.f;
	float _invinsibleTime = 0.f;
};

