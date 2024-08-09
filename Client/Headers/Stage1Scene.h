#pragma once
#include "DefaultStageScene.h"
//���ΰ��ӽ�������
namespace Engine
{
	class GameObject;
}

class CardManagement;
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
	bool UIinitialize() override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Stage1Scene* Create();

};