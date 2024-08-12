#pragma once
#include "MonoBehavior.h"

namespace
{
	class Animation;
}

class GridMovement;

class DefaultEnemyScript:public Engine::MonoBehavior
{
public:
	explicit DefaultEnemyScript(const wchar_t* name, const Vector3& startPos);
private:
	virtual ~DefaultEnemyScript() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	GridMovement* _movement = nullptr;
	Engine::Animation* _pAnimation = nullptr;
private:
	Vector3 _gridPosition = { 0.f,2.f,0.f };
	Vector3 _startPosition;
};

