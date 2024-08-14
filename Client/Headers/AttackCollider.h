#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Collider;
}

class Grid;
class AttackCollider : public Engine::MonoBehavior
{
public:
	explicit AttackCollider();
private:
	virtual ~AttackCollider() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void Initialize(const wchar_t* name, int width, int height);
	void OnCollider(float time, int coordX, int coordY);

private:
	std::vector<std::vector<std::pair<float, Engine::Collider*>>> _colliders;
	Grid* _pGrid = nullptr;
	int _maxCoordX = 0;
	int _maxCoordY = 0;
};

