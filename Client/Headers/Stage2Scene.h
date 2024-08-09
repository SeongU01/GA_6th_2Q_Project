#pragma once
#include "DefaultStageScene.h"
//���ΰ��ӽ�������
namespace Engine
{
	class GameObject;
}

class CardManager;
class MapManager;
class TimerSystem;
class Stage2Scene : public DefaultStageScene
{
private:
	explicit Stage2Scene() = default;
	virtual ~Stage2Scene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;
	bool UIinitialize() override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Stage2Scene* Create();
};