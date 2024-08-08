#pragma once
#include "Scene.h"
//���ΰ��ӽ�������
namespace Engine
{
	class GameObject;
}

class CardManagement;
class MapManager;
class Stage4Scene : public Engine::Scene
{
private:
	explicit Stage4Scene() = default;
	virtual ~Stage4Scene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	bool UIInitialize();
	void Free() override;

public:
	static Stage4Scene* Create();
private:
	Engine::GameObject* _pTimeObject = nullptr;
	CardManagement* _pCardManagement = nullptr;
	MapManager* _pMapManager = nullptr;
	wchar_t				_buffer[32]{};
};