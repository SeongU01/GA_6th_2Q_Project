#pragma once

#include "Base.h"

namespace Engine
{
    class TimeManager : public Base, public SingleTon<TimeManager>
    {
        friend class SingleTon;
    private:
        explicit TimeManager() { Initialize(); }
        virtual ~TimeManager() = default;
        NOCOPY(TimeManager)
    public:
        float GetSumTime() { return _elapsed; }
        void SetSumTime(float time) { _elapsed = time; }
        void SetSlowTime(float rate);
        float GetDeltaTime() { return 100 <= _deltaTime ? 0.001f : _deltaTime * _slowRate; }
        void Update();
        bool FrameLock(float frame);
    private:
        // CBase을(를) 통해 상속됨
        void Free() override;
        bool Initialize();
    private:
        LARGE_INTEGER _currTime;
        LARGE_INTEGER _oldTime;
        _ullong _fixTime;
        _ullong _fixFrame;
        float _deltaTime;
        float _globalDeltaTime;
        float _elapsed;
        float _slowRate = 1.f;
        float _frequency;
    };
}
