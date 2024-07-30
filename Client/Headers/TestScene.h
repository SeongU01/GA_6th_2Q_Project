#pragma once
#include "Scene.h"

namespace Engine
{
	class GameObject;
}

class TestScene : public Engine::Scene
{
private:
	explicit TestScene() = default;
	virtual ~TestScene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	void Free() override;
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	bool Initialize() override;

public:
	static TestScene* Create();

private:
	Engine::GameObject* _pObject = nullptr;
};

