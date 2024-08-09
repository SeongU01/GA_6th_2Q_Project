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
class Stage3Scene : public DefaultStageScene
{
private:
	explicit Stage3Scene() = default;
	virtual ~Stage3Scene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	bool UIinitialize() override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Stage3Scene* Create();
};