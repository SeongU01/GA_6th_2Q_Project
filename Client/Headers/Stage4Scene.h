#pragma once
#include "DefaultStageScene.h"
//메인게임스테이지
namespace Engine
{
	class GameObject;
}
class CardManagement;
class MapManager;
class TimerSystem;
class Stage4Scene : public DefaultStageScene
{
private:
	explicit Stage4Scene() = default;
	virtual ~Stage4Scene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	bool UIInitialize();
	void Free() override;

public:
	static Stage4Scene* Create();
private:
	TimerSystem* _pTimerSystem = nullptr;
	Engine::GameObject* _pTimeObject = nullptr;
	CardManagement* _pCardManagement = nullptr;
	MapManager* _pMapManager = nullptr;
};