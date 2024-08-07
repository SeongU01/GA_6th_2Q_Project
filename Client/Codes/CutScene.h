#pragma once
#include "Scene.h"

class CutScene : public Engine::Scene
{
private:
	explicit CutScene() = default;
	virtual ~CutScene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static CutScene* Create();
};