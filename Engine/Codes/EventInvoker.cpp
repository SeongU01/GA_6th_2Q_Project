#include "EventInvoker.h"
#include "TimeManager.h"

using namespace Engine;

Engine::EventInvoker::EventInvoker(const wchar_t* name)
	: Component(name)
{
}

void Engine::EventInvoker::Update(const float& deltaTime)
{
	float delta = deltaTime;

	if (_isUseGlobalDeltaTime)
		delta = TimeManager::GetInstance()->GetGlobalDeltaTime();

	auto iter = _eventActions.begin();

	for (iter; iter != _eventActions.end();)
	{
		iter->elapsed += delta;

		if (iter->activeTime < iter->elapsed)
		{
			iter->function();
			iter = _eventActions.erase(iter);
		}
		else
			++iter;
	}
}

void Engine::EventInvoker::Free()
{
}