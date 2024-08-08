#pragma once
#include "MonoBehavior.h"

class PlayerMP:public Engine::MonoBehavior
{
public:
	explicit PlayerMP(const wchar_t* name);
private:
	virtual ~PlayerMP() = default;
public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	int GetMP() { return _mp; }
	void SetMP(int mp) { _mp = mp; }
	__declspec(property(get = GetMP, put = SetMP))int mp;
private:
	void MPUpdate(const float& deltaTime);
	void NaturalRecovery(const float& deltaTime);
private:
	int _mp = 5;
	float _mpRecoveryTime = 0.f;
};

