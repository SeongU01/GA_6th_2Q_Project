#include "Timer.h"

using namespace Engine;

void Engine::Timer::Update(const float& deltaTime)
{
	for (auto& Timer : _vecTimer)
	{
		if (Timer.isActive)
			Timer.elapsed += deltaTime;
		else
			Timer.elapsed = 0.f;
	}
}

bool Engine::Timer::IsOverTime(int group, float time)
{
	return time <= _vecTimer[group].elapsed;
}

bool Engine::Timer::IsBetweenTime(int group, float first, float last)
{
	return (first <= _vecTimer[group].elapsed && last >= _vecTimer[group].elapsed);
}

void Engine::Timer::Free()
{
	_vecTimer.clear();
	_vecTimer.shrink_to_fit();
}