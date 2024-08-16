#pragma once
#include "Scene.h"

class Cut3Scene : public Engine::Scene
{
private:
	explicit Cut3Scene() = default;
	virtual ~Cut3Scene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Cut3Scene* Create();
};