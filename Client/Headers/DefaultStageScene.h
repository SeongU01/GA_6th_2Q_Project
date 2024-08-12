#pragma once
#include "Scene.h"
#include "DataManager.h"

namespace Engine {
	class CollisionManager;
}
class TimerSystem;
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
	virtual bool UIinitialize();

protected:
	void MakeObject(ObjectArrangeInfo& objInfo);
protected:
	TimerSystem* _pTimerSystem = nullptr;
	Engine::CollisionManager* _pCollisionManager = nullptr;
	wchar_t						_buffer[32]{};
};

