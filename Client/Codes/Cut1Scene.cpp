#include "Cut1Scene.h"
#include "Client_Define.h"



int Cut1Scene::Update(const float& deltaTime)
{
    return 0;
}

int Cut1Scene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool Cut1Scene::Initialize()
{
    return true;
}

void Cut1Scene::Free()
{
}

Cut1Scene* Cut1Scene::Create()
{
    return new Cut1Scene;
}