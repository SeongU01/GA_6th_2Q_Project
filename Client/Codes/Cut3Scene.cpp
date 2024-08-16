#include "Cut3Scene.h"
#include "Client_Define.h"


int Cut3Scene::Update(const float& deltaTime)
{
    return 0;
}

int Cut3Scene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool Cut3Scene::Initialize()
{
    return true;
}

void Cut3Scene::Free()
{
}

Cut3Scene* Cut3Scene::Create()
{
    return new Cut3Scene;
}