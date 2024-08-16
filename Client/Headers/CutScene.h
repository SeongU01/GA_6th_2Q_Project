#pragma once
#include "Scene.h"
#include "DataManager.h"
namespace Engine 
{
	class GameObject;
};

class CutScene : public Engine::Scene
{
private:
	virtual ~CutScene() = default;
public:
	explicit CutScene(int stage);
public:
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;
	void setScene();
public:
	static CutScene* Create(int stage);
	Engine::GameObject* pBObj = nullptr;
	Engine::GameObject* pFadeObj = nullptr;
	CutSceneInfo _info;
	int _stageNum = 1;
	float CutTime = 0.0f;
};