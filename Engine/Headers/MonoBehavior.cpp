#include "MonoBehavior.h"
#include "GameObject.h"

Engine::MonoBehavior::MonoBehavior(const char* name)
	: Component(name)
{
}

void Engine::MonoBehavior::OnCollisionEnter(CollisionInfo& info)
{
}

void Engine::MonoBehavior::OnCollision(CollisionInfo& info)
{
}

void Engine::MonoBehavior::OnCollisionExit(CollisionInfo& info)
{
}

void Engine::MonoBehavior::Free()
{
}