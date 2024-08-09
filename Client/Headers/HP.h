#pragma once
#include "MonoBehavior.h"

class HP :public Engine::MonoBehavior
{
public:
	explicit HP(const wchar_t* name,int maxHp);
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
	void SetHP(int hp) { _HP = hp; }
	__declspec(property(get = GetHP, put = SetHP))int hp;

	const int GetMaxHP() { return _maxHP; }

private:
	int _HP = 0;
	int _maxHP = 0;
};

