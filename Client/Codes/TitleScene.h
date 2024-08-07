#pragma once
#include "Scene.h"

class TitleScene : public Engine::Scene
{
private:
	explicit TitleScene() = default;
	virtual ~TitleScene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static TitleScene* Create();
};