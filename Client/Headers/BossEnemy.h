#pragma once
#include "GameObject.h"
class BossEnemy:public Engine::GameObject
{
private:
	explicit BossEnemy() = default;
	virtual ~BossEnemy() = default;

private:
	void Initialize(const Vector3& startPos, const std::wstring& _targetName);
public:
	static BossEnemy* Create(const Vector3& startPos, const std::wstring& _targetName);
};

