#include "Cut2Scene.h"
#include "Client_Define.h"


int Cut2Scene::Update(const float& deltaTime)
{
    return 0;
}

int Cut2Scene::LateUpdate(const float& deltaTime)
{
    return 0;
}

bool Cut2Scene::Initialize()
{
    return true;
}

void Cut2Scene::Free()
{
}

Cut2Scene* Cut2Scene::Create()
{
    return new Cut2Scene;
}