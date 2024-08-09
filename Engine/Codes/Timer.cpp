#include "Timer.h"

using namespace Engine;

Engine::Timer::Timer(const wchar_t* name, const int size)
	: Component(name)
{
	_timers.resize(size);
}

void Engine::Timer::Update(const float& deltaTime)
{
	for (auto& Timer : _timers)
	{
		if (Timer.isActive)
			Timer.elapsed += deltaTime;
		else
			Timer.elapsed = 0.f;
	}
}

bool Engine::Timer::IsOverTime(int group, float time)
{
	return time <= _timers[group].elapsed;
}

bool Engine::Timer::IsBetweenTime(int group, float first, float last)
{
	return (first <= _timers[group].elapsed && last >= _timers[group].elapsed);
}

void Engine::Timer::Free()
{
	_timers.clear();
	_timers.shrink_to_fit();
}