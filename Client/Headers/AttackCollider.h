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
		unsigned long long Attribute;
		int AttributeStack;
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
	const AttackInfo& GetCurrentAttackInfo(int index) const { return _info[index]; }
	void Initialize(const wchar_t* name, int width, int height);
	void OnCollider(float delay, float duration, int coordX, int coordY, const AttackInfo& info, int index);
	void ResizeCollider();
private:
	std::vector<std::vector<std::tuple<float, float, Engine::Collider*>>> _colliders;
	AttackInfo _info[2];
	Grid* _pGrid = nullptr;
	int _maxCoordX = 0;
	int _maxCoordY = 0;
};

