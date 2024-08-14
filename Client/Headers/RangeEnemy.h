#pragma once
#include "GameObject.h"

class RangeEnemy :public Engine::GameObject
{
private:
	explicit RangeEnemy() = default;
	virtual ~RangeEnemy() = default;

private:
	void Initialize(const Vector3& startPos, const std::wstring& _targetName);
public:
	static RangeEnemy* Create(const Vector3& startPos, const std::wstring& _targetName);
};

