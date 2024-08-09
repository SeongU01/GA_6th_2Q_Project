#pragma once
#include "Component.h"

namespace Engine
{
    class Timer : public Component
    {
    private:
        typedef struct TimerInfo
        {
            float elapsed = 0.f;
            bool isActive = false;
        }TIMER;
    public:
        explicit Timer(const wchar_t* name, const int size);
    private:
        virtual ~Timer() = default;

    public:
        void Update(const float& deltaTime) override;

    public:
        bool IsOverTime(int group, float time);
        bool IsBetweenTime(int group, float first, float last);
        void SetActive(int group, bool isActive) { _timers[group].isActive = isActive; }
        void SetElapsed(int group, float elapsed) { _timers[group].elapsed = elapsed; }
        TIMER& operator[](int index) { return _timers[index]; }

    private:
        // CComponent을(를) 통해 상속됨
        void Free() override;

    private:
        std::vector<TimerInfo> _timers;
    };
}