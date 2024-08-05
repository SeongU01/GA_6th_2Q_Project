 #include "TimeManager.h"

using namespace Engine;

bool TimeManager::Initialize()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    _frequency = float(frequency.QuadPart);
    QueryPerformanceCounter(&_oldTime);
    QueryPerformanceCounter(&_currTime);

    return true;
}

void Engine::TimeManager::SetSlowTime(float rate)
{
    _slowRate = rate;
}

void TimeManager::Update()
{
    _oldTime = _currTime;
    QueryPerformanceCounter(&_currTime);

    _globalDeltaTime = (_currTime.QuadPart - _oldTime.QuadPart) / _frequency ;
    _deltaTime = _globalDeltaTime;

    _elapsed += _globalDeltaTime;
}

bool TimeManager::FrameLock(float frame)
{
    /*_fixTime = _deltaTime;
    _fixFrame = 1000.0 / frame;

    if (_fixFrame <= _fixTime)
    {
        _fixTime = 0;
        return true;
    }*/
    return false;
}

void TimeManager::Free()
{
}
