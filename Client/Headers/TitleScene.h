#pragma once
#include "Scene.h"

namespace Engine
{
	class Animation;
}

class TitleScene : public Engine::Scene
{
private:
	explicit TitleScene() = default;
	virtual ~TitleScene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	bool UIInitialize();
	void Free() override;

public:
	static TitleScene* Create();

private:
	Engine::Animation* _pAnimation = nullptr;
	Engine::Animation* _pFirefly = nullptr;
	bool _isRevers = false;
	bool _isFirstInit = false;
};