#include "Layer.h"
#include "GameObject.h"

using namespace Engine;

void Engine::Layer::Start()
{
    for (auto& pair : _objectData)
    {
        for (auto& object : pair.second)
        {
            object->Start();
        }
    }
}

void Layer::FixUpdate()
{
    for (auto& pair : _objectData)
    {
        for (auto& object : pair.second)
        {
            object->FixedUpdate();
        }
    }
}

int Layer::Update(const float& deltaTime)
{
    int isEvent = 0;

    for (auto& pair : _objectData)
    {
        for (auto& object : pair.second)
        {
            if (object->_isDead)
                continue;

            isEvent = object->Update(deltaTime);

            if (GameState::Game_End == isEvent)
                return isEvent;
        }
    }

    return isEvent;
}

int Layer::LateUpdate(const float& deltaTime)
{
    int isEvent = 0;
   
    for (auto& pair : _objectData)
    {
        auto iter = pair.second.begin();
        auto iter_end = pair.second.end();

        for (iter; iter != iter_end;)
        {
            if ((*iter)->_isDead)
            {
                SafeRelease(*iter);
                iter = pair.second.erase(iter);
            }
            else
            {
                (*iter)->LateUpdate(deltaTime);
                ++iter;
            }
        }
    }

    return isEvent;
}

void Engine::Layer::AddRenderer()
{
    for (auto& pair : _objectData)
    {
        for (auto& object : pair.second)
        {
            if (!object->_isDead && object->IsActive())
                object->AddRenderer();
        }
    }
}

void Engine::Layer::ClearObjectList(const wchar_t* listTag)
{
    if (0 == _objectData[listTag].size())
        return;

    for (auto& object : _objectData[listTag])
    {
        object->SetDead();
    }
}

void Engine::Layer::ClearAllObjectList()
{
    for (auto& pair : _objectData)
    {
        for (auto& object : pair.second)
        {
            if (!object->_dontDestroy)
                object->SetDead();
        }
    }
}

void Engine::Layer::RemoveAll()
{
    for (auto& pair : _objectData)
    {
        for (auto& object : pair.second)
        {
            object->SetDead();
        }
    }
}

GameObject* Engine::Layer::FindObject(const wchar_t* listTag, const wchar_t* objectTag)
{
    if (0 == _objectData[listTag].size())
        return nullptr;

    for (auto& object : _objectData[listTag])
    {
        if (object->_isDead)
            continue;

        if (*object == objectTag)
            return object;
    }

    return nullptr;
}

bool Layer::AddObject(const wchar_t* listTag, GameObject* pObject)
{
    if (nullptr == pObject)
        return false;

    _objectData[listTag].push_back(pObject);

    return true;
}

void Layer::Free()
{
    for (auto& pair : _objectData)
    {
        for (auto& object : pair.second)
            SafeRelease(object);

        pair.second.clear();
    }

    _objectData.clear();
}

Layer* Layer::Create()
{
    return new Layer;
}
