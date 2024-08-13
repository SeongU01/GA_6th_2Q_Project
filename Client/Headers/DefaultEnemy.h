#pragma once
#include "GameObject.h"

class DefaultEnemy :public Engine::GameObject
{
private:
	explicit DefaultEnemy() = default;
	virtual ~DefaultEnemy() = default;

private:
	void Initialize(const Vector3& startPos, const std::wstring& _targetName);
public:
	static DefaultEnemy* Create(const Vector3& startPos,const std::wstring& _targetName);
};