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
    if (_playTime > 0.0f)
    {
        _playTime -= deltaTime;
        _playTime = _playTime < 0.0f ? 0 : _playTime;//끝난경우 0으로 다시 초기화
    }
    float timer = GetRemainingTime();

    //시간정지
    if (Input::IsKeyDown(DIK_SPACE))
    {
        _isStopTime = !_isStopTime;
        if (_isStopTime) _slowTime = 0.0f;
        else _slowTime = 1.0f;
                
        Time::SetSlowTime(_slowTime);
    }
}

void TimerSystem::LateUpdate(const float& deltaTime)
{
    _curTime = std::clamp(_curTime, 0.f, _maxTime);
}