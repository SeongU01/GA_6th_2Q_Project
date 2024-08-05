#include "TimerSystem.h"
#include "Client_Define.h"

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

    //시간정지
    if (Input::IsKeyDown(DIK_SPACE))
    {
        if (_slowTime == 0.0f)
        {
            _slowTime=1.0f;
        }
        else
        {
            _slowTime = 0.0f;
        }
        Time::SetSlowTime(_slowTime);
    }
}

void TimerSystem::LateUpdate(const float& deltaTime)
{
}
