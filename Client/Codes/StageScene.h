#pragma once
#include "Scene.h"
//���ΰ��ӽ�������
class StageScene : public Engine::Scene
{
private:
	explicit StageScene() = default;
	virtual ~StageScene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static StageScene* Create();
};