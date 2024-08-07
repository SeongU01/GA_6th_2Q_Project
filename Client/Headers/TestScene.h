#pragma once
#include "Scene.h"

namespace Engine
{
	class GameObject;
}

class CardManagement;
class MapManager;
class TestScene : public Engine::Scene
{
private:
	explicit TestScene() = default;
	virtual ~TestScene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static TestScene* Create();

private:
	Engine::GameObject* _pTimeObject = nullptr;
	CardManagement* _pCardManagement = nullptr;
	MapManager* _pMapManager = nullptr;
	wchar_t				_buffer[32]{};
};