#include "EventInvoker.h"

using namespace Engine;

void Engine::EventInvoker::Update(const float& deltaTime)
{
	auto iter = _eventActions.begin();

	for (iter; iter != _eventActions.end();)
	{
		iter->elapsed += deltaTime;

		if (iter->activeTime < iter->elapsed)
		{
			std::invoke(iter->function);
			iter = _eventActions.erase(iter);
		}
		else
			++iter;
	}
}

void Engine::EventInvoker::Free()
{
}