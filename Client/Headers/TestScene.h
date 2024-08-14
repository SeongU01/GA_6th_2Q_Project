#pragma once
#include "DefaultStageScene.h"

namespace Engine
{
	class GameObject;
	class CollisionManager;
}

class CardManager;
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
	bool UIinitialize() override;
	bool Initialize() override;
	void Free() override;

public:
	static TestScene* Create();

private:
	Engine::GameObject*			_pTimeObject = nullptr;
	CardManager*				_pCardManager = nullptr;
	DataManager*				_pDataManager = nullptr;
	wchar_t						_buffer[32]{};
};