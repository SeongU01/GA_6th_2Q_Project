#pragma once
#include "Scene.h"
//메인게임스테이지
namespace Engine
{
	class GameObject;
}

class CardManagement;
class MapManager;
class Stage1Scene : public Engine::Scene
{
private:
	explicit Stage1Scene() = default;
	virtual ~Stage1Scene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool Initialize() override;
	void Free() override;

public:
	static Stage1Scene* Create();
private:
	Engine::GameObject* _pTimeObject = nullptr;
	CardManagement* _pCardManagement = nullptr;
	MapManager* _pMapManager = nullptr;
	wchar_t				_buffer[32]{};
};