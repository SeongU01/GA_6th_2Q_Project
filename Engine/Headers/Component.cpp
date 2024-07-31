#include "Component.h"

Engine::Transform* Engine::Component::GetTransform()
{
    return _pOwner->GetTransform();
}
