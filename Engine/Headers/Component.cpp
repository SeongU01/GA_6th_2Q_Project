#include "Component.h"

using namespace Engine;

Engine::Transform& Engine::Component::GetTransform()
{
    return _pOwner->GetTransform();
}

Engine::GameObject& Engine::Component::GetOwner()
{
    return *_pOwner;
}
