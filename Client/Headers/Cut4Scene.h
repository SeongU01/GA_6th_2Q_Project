#pragma once
#include "Scene.h"

class Cut4Scene : public Engine::Scene
{
private:
	explicit Cut4Scene() = default;
	virtual ~Cut4Scene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Cut4Scene* Create();
};