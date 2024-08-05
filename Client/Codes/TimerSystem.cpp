#include "TimerSystem.h"
#include "TimeManager.h"
TimerSystem::TimerSystem()
	:MonoBehavior("TimeSystem")
{
}
void TimerSystem::Awake()
{
}

void TimerSystem::Start()
{
}

void TimerSystem::FixedUpdate()
{
}

void TimerSystem::Update(const float& deltaTime)
{
	_curTime += deltaTime;
    float timer = GetRemainingTime();

    swprintf(_buffer, sizeof(_buffer) / sizeof(_buffer[0]), L"Timer : %02d:%02d", (int)timer, (int)(timer * 100) % 100);
    _Text->SetText(_buffer);
}

void TimerSystem::LateUpdate(const float& deltaTime)
{
}
