#include "Cut4Scene.h"
#include "Client_Define.h"

int Cut4Scene::Update(const float& deltaTime)
{
    return 0;
}

int Cut4Scene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool Cut4Scene::Initialize()
{
    return true;
}

void Cut4Scene::Free()
{
}

Cut4Scene* Cut4Scene::Create()
{
    return new Cut4Scene;
}