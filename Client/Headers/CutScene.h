#pragma once
#include "Scene.h"
#include "DataManager.h"
namespace Engine 
{
	class GameObject;
};

class Player;
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
	Engine::GameObject* _pBObj = nullptr;
	Engine::GameObject* _pFadeObj = nullptr;
	Player*				 _pPlayer = nullptr;
	CutSceneInfo _info;
	int _stageNum = 1;
	float _cutTime = 0.0f;
};