#pragma once
#include "Component.h"

namespace Engine
{
    class State;
    class FiniteStateMachine : public Component
    {
    public:
        explicit FiniteStateMachine(const wchar_t* name, const int size);
    private:
        virtual ~FiniteStateMachine() = default;

    public:
        void Update(const float& deltaTime) override;
        void LateUpdate(const float& deltaTime) override;
        void Reset();
        void Reset(const int& group);

    public:
        State* GetCurrState(const int& state) { return _states[state]; }
        int GetCurrState() const { return _currStateIndex; }
        void AddState(const int& group, State* pState)
        {
            if (nullptr == pState)
                return;

            _states[group] = pState;
        }
        void ChangeState(const int& nextState);

    private:
        // Component을(를) 통해 상속됨
        void Free() override;

    private:
        std::vector<State*> _states;
        int                 _currStateIndex = 0;
        int                 _prevStateIndex = 0;
    };
}