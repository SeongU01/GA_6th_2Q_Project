#pragma once
#include "DefaultStageScene.h"
//���ΰ��ӽ�������
namespace Engine
{
	class GameObject;
}

class CardManagement;
class MapManager;
class TimerSystem;
class Stage1Scene : public DefaultStageScene
{
private:
	explicit Stage1Scene() = default;
	virtual ~Stage1Scene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	bool UIInitialize();
	void Free() override;

public:
	static Stage1Scene* Create();
private:
	TimerSystem* _pTimerSystem = nullptr;
	Engine::GameObject* _pTimeObject = nullptr;
	CardManagement* _pCardManagement = nullptr;
	MapManager* _pMapManager = nullptr;
};