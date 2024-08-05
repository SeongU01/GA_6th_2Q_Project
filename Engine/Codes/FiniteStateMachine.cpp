#include "FiniteStateMachine.h"
#include "State.h"

using namespace Engine;

Engine::FiniteStateMachine::FiniteStateMachine(const wchar_t* name, const int size)
	: Component(name)
{
	_states.resize(size);
}

void Engine::FiniteStateMachine::Update(const float& deltaTime)
{
	_states[_currStateIndex]->Update(deltaTime);
}

void Engine::FiniteStateMachine::LateUpdate(const float& deltaTime)
{
	int nextState = _states[_currStateIndex]->LateUpdate(deltaTime);

	if (0 < nextState)
	{
		_states[_currStateIndex]->OnExit();
		_currStateIndex = nextState;
		_states[_currStateIndex]->OnStart();
	}
}

void Engine::FiniteStateMachine::Reset()
{
	for (auto& state : _states)
	{
		if (nullptr != state)
			state->Reset();
	}
}

void Engine::FiniteStateMachine::Reset(const int& group)
{
	_states[group]->Reset();
}

void Engine::FiniteStateMachine::ChangeState(const int& nextState)
{
	if (0 != _currStateIndex) _states[_currStateIndex]->OnExit();
	_currStateIndex = nextState;
	if (0 != _currStateIndex) _states[_currStateIndex]->OnStart();
}

void Engine::FiniteStateMachine::Free()
{
	for (auto& State : _states)
		SafeRelease(State);
}