#include "SceneManager.h"
#include "Scene.h"
#include "Layer.h"

using namespace Engine;

void Engine::SceneManager::FixedUpdate()
{
	for (auto& Layer : _layers)
		Layer->FixUpdate();
}

int Engine::SceneManager::Update(const float& deltaTime)
{
	if (nullptr == _pScene || !_isSetUp)
		return GameState::Error;

	int isEvent = 0;
	for (auto& Layer : _layers)
	{
		isEvent = Layer->Update(deltaTime);
		if (GameState::Game_End == isEvent)
			return isEvent;
	}

	_pScene->Update(deltaTime);

	return 0;
}

int Engine::SceneManager::LateUpdate(const float& deltaTime)
{
	if (nullptr == _pScene || !_isSetUp)
		return GameState::Error;

	int isEvent = 0;

	for (auto& Layer : _layers)
	{
		isEvent = Layer->LateUpdate(deltaTime);
		if (GameState::Game_End == isEvent)
			return isEvent;
	}

	_pScene->LateUpdate(deltaTime);

	return 0;
}

void Engine::SceneManager::AddRenderGroup()
{
	for (auto& Layer : _layers)
		Layer->AddRenderer();
}

bool Engine::SceneManager::SetUpLayer(int layerSize)
{
	_layers.reserve(layerSize);
	for (int i = 0; i < layerSize; i++)
		_layers.push_back(Layer::Create());

	return true;
}

bool Engine::SceneManager::ChangeScene(Scene* pScene)
{
	if (nullptr == pScene)
		return false;

	if (nullptr != _pScene)
		SafeRelease(_pScene);

	for (auto& Layer : _layers)
		Layer->ClearAllObjectList();

	_pScene = pScene;
	_pScene->Initialize();
	_isSetUp = true;

	return false;
}

void Engine::SceneManager::ClearObjectList(int layerGroup, const char* listTag)
{
	_layers[layerGroup]->ClearObjectList(listTag);
}

void Engine::SceneManager::ClearLayer(int layerGroup)
{
	_layers[layerGroup]->ClearAllObjectList();
}

std::list<GameObject*>* Engine::SceneManager::GetObjectList(int layerGroup, const char* listTag)
{
	return _layers[layerGroup]->GetObjectList(listTag);
}

GameObject* Engine::SceneManager::GetObject(int layerGroup, const char* listTag, const char* objectTag)
{
	return _layers[layerGroup]->GetObject(listTag, objectTag);
}

bool Engine::SceneManager::AddObjectInLayer(int layerGroup, const char* listTag, GameObject* pObject)
{
	if (_layers.empty())
		return false;

	_layers[layerGroup]->AddObject(listTag, pObject);

	return true;
}

void Engine::SceneManager::Free()
{
	std::for_each(_layers.begin(), _layers.end(), SafeRelease<Layer*>);
	_layers.clear();
	_layers.shrink_to_fit();

	SafeRelease(_pScene);
}

SceneManager* Engine::SceneManager::Create()
{
	return new SceneManager;
}