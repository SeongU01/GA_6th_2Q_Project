#include "MonoBehavior.h"
#include "GameObject.h"

Engine::MonoBehavior::MonoBehavior(const char* name)
	: Component(name)
{
}

void Engine::MonoBehavior::Initialize()
{
	_pTransform = _pOwner->GetTransform();
	Awake();
}

void Engine::MonoBehavior::Free()
{
}
