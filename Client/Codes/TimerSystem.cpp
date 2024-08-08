#include "TimerSystem.h"
#include "Client_Define.h"

TimerSystem::TimerSystem()
	:MonoBehavior(L"TimeSystem")
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

    //�ð�����
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
