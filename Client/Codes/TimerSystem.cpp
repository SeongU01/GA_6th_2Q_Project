#include "TimerSystem.h"

// Component
#include "HP.h"

#include "EventManager.h"
#include "Client_Define.h"

TimerSystem::TimerSystem()
	:MonoBehavior(L"TimeSystem")
{
}

void TimerSystem::TimeStop()
{
    EventManager* pEventManager = EventManager::GetInstance();

    if (pEventManager->IsStopGame() || pEventManager->IsPlayerDeath() || pEventManager->IsTutorial())
        return;

    _isStopTime = !_isStopTime;
    pEventManager->SetTimeStop(_isStopTime);

    if (_isStopTime)
    {
        Sound::PlaySound("Effect_Sound_FX_Time_Pause", (int)SoundGroup::Time, 0.8f, false);
        _slowTime = 0.0f;

        for (int i = 0; i < (int)SoundGroup::End; i++)
        {
            if (i == (int)SoundGroup::Voice || i == (int)SoundGroup::SFX ||
                i == (int)SoundGroup::Card || i == (int)SoundGroup::AddSFX ||
                i == (int)SoundGroup::BGM || i == (int)SoundGroup::Operator
                || i == (int)SoundGroup::Time)
                continue;
            Sound::PauseSound(i, true);
        }
        Sound::SetVolume((int)SoundGroup::BGM, 0.1f);
    }
    else
    {
        Sound::SetVolume((int)SoundGroup::BGM, 0.5f);
        Sound::StopSound((int)SoundGroup::Time);
        for (int i = 0; i < (int)SoundGroup::End; i++)
        {
            Sound::PauseSound(i, false);
        }
        _slowTime = 1.0f;
    }

    Time::SetSlowTime(_slowTime);
}

void TimerSystem::TutorialTimeStop(bool isActive)
{
    EventManager* pEventManager = EventManager::GetInstance();

    _isStopTime = isActive;
    pEventManager->SetTimeStop(_isStopTime);
    pEventManager->SetActiveTutorial(_isStopTime);

    if (_isStopTime)
    {
        _slowTime = 0.0f;
    }
    else
    {
        _slowTime = 1.0f;
    }

    Time::SetSlowTime(_slowTime);
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
        Sound::PlaySound("Voice_Sound_Voice_Operator_TimeOut_30", (int)SoundGroup::Operator, 0.8f, false);
    }
    else if (timer <= 15.f && timer >= 10.f && _isNotice)
    {
        _isNotice = false;
    }
    else if (timer <= 10.f && !_isNotice)
    {
        _isNotice = true;
        Sound::PlaySound("Effect_Sound_FX_Notify_TimeOut_10", (int)SoundGroup::Time, 0.8f, false);
        Sound::PlaySound("Voice_Sound_Voice_Operator_TimeOut_10", (int)SoundGroup::Operator, 0.8f, false);
    }
    //시간정지
    if (Input::IsKeyDown(DIK_SPACE)) 
    {
        if(!_isStopTime)  Sound::PlaySound("Effect_Sound_FX_Time_WhilePause", (int)SoundGroup::Time, 0.8f, true);
        TimeStop();
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