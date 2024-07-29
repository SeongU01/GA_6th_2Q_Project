#pragma once
#include "Scene.h"

class TestScene : public Engine::Scene
{
private:
	explicit TestScene() = default;
	virtual ~TestScene() = default;

public:
	// Scene을(를) 통해 상속됨
	void Free() override;
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	bool Initialize() override;

public:
	static TestScene* Create();
};

