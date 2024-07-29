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
        explicit Timer(const char* name) { _name = name; }
    private:
        virtual ~Timer() = default;

    public:
        virtual void Update(const float& deltaTime);
        template <typename T>
        void Initialize(const T& groupSize)
        {
            _vecTimer.resize(static_cast<int>(groupSize));
        }
        bool IsOverTime(int group, float time);
        bool IsBetweenTime(int group, float first, float last);
        void SetActive(int group, bool isActive) { _vecTimer[group].isActive = isActive; }
        void SetElapsed(int group, float elapsed) { _vecTimer[group].elapsed = elapsed; }
        TIMER& operator[](int index) { return _vecTimer[index]; }

    private:
        // CComponent을(를) 통해 상속됨
        void Free() override;

    private:
        std::vector<TimerInfo> _vecTimer;
    };
}