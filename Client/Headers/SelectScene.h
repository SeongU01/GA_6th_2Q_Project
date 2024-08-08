#pragma once
#include "Scene.h"

class Canvas;
class SelectScene : public Engine::Scene
{
private:
	explicit SelectScene() = default;
	virtual ~SelectScene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;
	bool UIInitialize();

public:
	static SelectScene* Create();
private:
	Canvas* UIFrame;
};