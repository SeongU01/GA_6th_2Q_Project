#pragma once
#include "Scene.h"
#include "DataManager.h"
namespace Engine
{
	class GameObject;
	class CollisionManager;
}

class CardSystem;
class CardManagement;
class DataManager;

class DefaultStageScene : public Engine::Scene
{
protected:
	explicit DefaultStageScene() = default;
	virtual ~DefaultStageScene() = default;
public:
	// Scene을(를) 통해 상속됨
	virtual int Update(const float& deltaTime) override;
	virtual int LateUpdate(const float& deltaTime) override;

	virtual bool Initialize() override;
	virtual void Free() override;

protected:
	void MakeObject(ObjectArrangeInfo& objInfo);
protected:
	Engine::GameObject* _pTimeObject = nullptr;
	Engine::CollisionManager* _pCollisionManager = nullptr;
	CardManagement* _pCardManagement = nullptr;
	CardSystem* _pCardSystem = nullptr;
	DataManager* _pDataManager = nullptr;
	wchar_t						_buffer[32]{};
};

