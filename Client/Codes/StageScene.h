#pragma once
#include "Scene.h"
//메인게임스테이지
class StageScene : public Engine::Scene
{
private:
	explicit StageScene() = default;
	virtual ~StageScene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static StageScene* Create();
};