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
	struct AttackInfo
	{
		unsigned long long additiveState;
		int additiveStateStack;
		int damage;
	};
public:
	explicit AttackCollider();
private:
	virtual ~AttackCollider() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	const AttackInfo& GetCurrentAttackInfo() const { return _info; }
	void Initialize(const wchar_t* name, int width, int height);
	void OnCollider(float time, int coordX, int coordY, const AttackInfo& info);

private:
	std::vector<std::vector<std::pair<float, Engine::Collider*>>> _colliders;
	AttackInfo _info;
	Grid* _pGrid = nullptr;
	int _maxCoordX = 0;
	int _maxCoordY = 0;
};

