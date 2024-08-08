#pragma once
#include "DefaultStageScene.h"

namespace Engine
{
	class GameObject;
	class CollisionManager;
}

class CardSystem;
class CardManagement;
class DataManager;
class TestScene : public DefaultStageScene
{
private:
	explicit TestScene() = default;
	virtual ~TestScene() = default;

public:
	// Scene을(를) 통해 상속됨
	int Update(const float& deltaTime) override;
	int LateUpdate(const float& deltaTime) override;

private:
	bool UIInitialize();
	bool Initialize() override;
	void Free() override;

public:
	static TestScene* Create();

private:
	Engine::GameObject*			_pTimeObject = nullptr;
	Engine::CollisionManager*	_pCollisionManager = nullptr;
	CardManagement*				_pCardManagement = nullptr;
	CardSystem*					_pCardSystem = nullptr;
	DataManager*					_pDataManager = nullptr;
	wchar_t						_buffer[32]{};
};