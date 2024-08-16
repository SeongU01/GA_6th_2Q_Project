#pragma once
#include "Scene.h"

class Cut2Scene : public Engine::Scene
{
private:
	explicit Cut2Scene() = default;
	virtual ~Cut2Scene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Cut2Scene* Create();
};