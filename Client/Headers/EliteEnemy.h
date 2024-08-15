#pragma once
#include "GameObject.h"
class EliteEnemy:public Engine::GameObject
{
private:
	explicit EliteEnemy() = default;
	virtual ~EliteEnemy() = default;

private:
	void Initialize(const Vector3& startPos, const std::wstring& _targetName);
public:
	static EliteEnemy* Create(const Vector3& startPos, const std::wstring& _targetName);
};

