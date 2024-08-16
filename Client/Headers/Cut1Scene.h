#pragma once
#include "Scene.h"

class Cut1Scene : public Engine::Scene
{
private:
	explicit Cut1Scene() = default;
	virtual ~Cut1Scene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Cut1Scene* Create();
};