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
    if (timer > 30) // 주황 게이지 변경
    {

        float rate = (1 + int((timer - 30.f) / 5.f)) / 6.f;
        int rates = 6 - ((timer - 30.f) / 5);
        _RemainingUI[1]->SetOffsetPosition(Vector3(-10.8 * rates, 0.f, 0.f));
        _RemainingUI[1]->SetScale({ 0.5f * rate, 1.0f, 0.f }); 
      //  _RemainingUI[1]->SetOffsetPosition(Vector3(-(126* 0.5f *0.5f* (1.f - rate)), 0.f, 0.f)); 흐아아아앙
    }
    else // 빨강 게이지 변경
    {
        _RemainingUI[1]->SetScale({ 0.f,0.f,0.f });
        float rate = (1 + int(timer / 5.f)) / 6.f;
        int rates = 6 - (timer / 5);
        _RemainingUI[0]->SetOffsetPosition(Vector3(-10.8 * rates, 0.f, 0.f));
        _RemainingUI[0]->SetScale({ 0.5f * rate, 1.0f, 0.f });
    }

    if (timer <= 0) { 
        Time::SetSlowTime(0.0f);   
        _RemainingUI[0]->SetScale({ 0.f,0.f,0.f });
    }
}

void TimerSystem::LateUpdate(const float& deltaTime)
{
}
