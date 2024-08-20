#include "TimerSystem.h"

// Component
#include "HP.h"

#include "EventManager.h"
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
    
    //사운드 경보
    if (timer <= 30.f && timer >= 20.f && !_isNotice)
    {
        _isNotice = true;
        Sound::PlaySound("Effect_Sound_FX_Notify_TimeOut_30", (int)SoundGroup::Time, 0.8f, false);
        Sound::StopSound((int)SoundGroup::Voice);
        Sound::PlaySound("Voice_Sound_Voice_Operator_TimeOut_30", (int)SoundGroup::Voice, 0.8f, false);
    }
    else if (timer <= 15.f && timer >= 10.f && _isNotice)
    {
        _isNotice = false;
    }
    else if (timer <= 10.f && !_isNotice)
    {
        _isNotice = true;
        Sound::PlaySound("Effect_Sound_FX_Notify_TimeOut_10", (int)SoundGroup::Time, 0.8f, false);
        Sound::StopSound((int)SoundGroup::Voice);
        Sound::PlaySound("Voice_Sound_Voice_Operator_TimeOut_10", (int)SoundGroup::Voice, 0.8f, false);
    }
    //시간정지
    if (Input::IsKeyDown(DIK_SPACE))
    {
        EventManager* pEventManager = EventManager::GetInstance();

        if (pEventManager->IsStopGame() || pEventManager->IsPlayerDeath())
            return;

        _isStopTime = !_isStopTime;
        pEventManager->SetTimeStop(_isStopTime);

        if (_isStopTime)
        {
            Sound::PlaySound("Effect_Sound_FX_Time_Pause", (int)SoundGroup::Time, 0.8f, false);
            _slowTime = 0.0f;
        }
        else
        {
            _slowTime = 1.0f;
        }

        Time::SetSlowTime(_slowTime);
    }
}

void TimerSystem::LateUpdate(const float& deltaTime)
{
    _curTime = std::clamp(_curTime, 0.f, _maxTime);

    if (0.f >= GetRemainingTime())
    {
        GetComponent<HP>()->hp = 0;
    }
}