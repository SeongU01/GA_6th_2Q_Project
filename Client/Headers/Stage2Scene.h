#pragma once
#include "Scene.h"
//���ΰ��ӽ�������
namespace Engine
{
	class GameObject;
}

class CardManagement;
class MapManager;
class Stage2Scene : public Engine::Scene
{
private:
	explicit Stage2Scene() = default;
	virtual ~Stage2Scene() = default;

public:
	// Scene��(��) ���� ��ӵ�
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Stage2Scene* Create();
private:
	Engine::GameObject* _pTimeObject = nullptr;
	CardManagement* _pCardManagement = nullptr;
	MapManager* _pMapManager = nullptr;
	wchar_t				_buffer[32]{};
};