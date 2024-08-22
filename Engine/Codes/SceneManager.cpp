#include "SceneManager.h"
#include "Scene.h"
#include "Layer.h"

using namespace Engine;

void Engine::SceneManager::Start()
{
	for (auto& layer : _layers)
		layer->Start();
}

void Engine::SceneManager::FixedUpdate()
{
	for (auto& layer : _layers)
		layer->FixUpdate();
}

int Engine::SceneManager::Update(const float& deltaTime)
{
	if (nullptr == _pScene || !_isSetUp)
		return GameState::Error;

	int isEvent = 0;
	for (auto& layer : _layers)
	{
		isEvent = layer->Update(deltaTime);
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

	for (auto& layer : _layers)
	{
		isEvent = layer->LateUpdate(deltaTime);
		if (GameState::Game_End == isEvent)
			return isEvent;
	}

	_pScene->LateUpdate(deltaTime);

	return 0;
}

void Engine::SceneManager::AddRenderGroup()
{
	for (auto& layer : _layers)
		layer->AddRenderer();
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

	for (auto& layer : _layers)
		layer->ClearAllObjectList();

	_pScene = pScene;
	_pScene->Initialize();
	_isSetUp = true;

	return false;
}

void Engine::SceneManager::ClearObjectList(int layerGroup, const wchar_t* listTag)
{
	_layers[layerGroup]->ClearObjectList(listTag);
}

void Engine::SceneManager::ClearLayer(int layerGroup)
{
	_layers[layerGroup]->ClearAllObjectList();
}

void Engine::SceneManager::RemoveAll()
{
	for (auto& layer : _layers)
		layer->RemoveAll();
}

std::list<GameObject*>* Engine::SceneManager::FindObjectList(int layerGroup, const wchar_t* listTag)
{
	return _layers[layerGroup]->FindObjectList(listTag);
}

GameObject* Engine::SceneManager::FindObject(int layerGroup, const wchar_t* listTag, const wchar_t* objectTag)
{
	return _layers[layerGroup]->FindObject(listTag, objectTag);
}

bool Engine::SceneManager::AddObjectInLayer(int layerGroup, const wchar_t* listTag, GameObject* pObject)
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