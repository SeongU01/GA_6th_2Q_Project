#include "MonoBehavior.h"
#include "GameObject.h"

Engine::MonoBehavior::MonoBehavior(const char* name)
	: Component(name)
{
}

void Engine::MonoBehavior::Free()
{
}