#include "MonoBehavior.h"
#include "GameObject.h"

Engine::MonoBehavior::MonoBehavior(const wchar_t* name)
	: Component(name)
{
}

void Engine::MonoBehavior::Free()
{
}