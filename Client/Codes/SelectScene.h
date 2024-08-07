#pragma once
#include "Scene.h"

class SelectScene : public Engine::Scene
{
private:
	explicit SelectScene() = default;
	virtual ~SelectScene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static SelectScene* Create();
};