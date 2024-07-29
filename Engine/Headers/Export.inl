#pragma once

// Layer
void ClearLayer(int layerGroup)
{
	Engine::GameManager::GetInstance()->ClearLayer(layerGroup);
}
void ClearObjectList(int layerGroup, const char* listTag)
{
	Engine::GameManager::GetInstance()->ClearObjectList(layerGroup, listTag);
}
std::list<Engine::GameObject*>* GetObjectList(int layerGroup, const char* listTag)
{
	return Engine::GameManager::GetInstance()->GetObjectList(layerGroup, listTag);
}
Engine::GameObject* GetObject(int layerGroup, const char* listTag, const char* objectTag)
{
	return Engine::GameManager::GetInstance()->GetObject(layerGroup, listTag, objectTag);
}
bool AddObjectInLayer(int layerGroup, const char* listTag, Engine::GameObject* pObject)
{
	return Engine::GameManager::GetInstance()->AddObjectInLayer(layerGroup, listTag, pObject);
}