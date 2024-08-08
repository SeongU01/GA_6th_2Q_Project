#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class GameObject;
}
class DeckSystem : public Engine::MonoBehavior
{
public:
	explicit DeckSystem();
private:
	virtual ~DeckSystem() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	std::list<Engine::GameObject*> _objects;
};