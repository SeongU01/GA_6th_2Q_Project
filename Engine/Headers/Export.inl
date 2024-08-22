#pragma once

// Layer
void ClearLayer(int layerGroup)
{
	Engine::GameManager::GetInstance()->ClearLayer(layerGroup);
}
void ClearObjectList(int layerGroup, const wchar_t* listTag)
{
	Engine::GameManager::GetInstance()->ClearObjectList(layerGroup, listTag);
}

std::list<Engine::GameObject*>* FindObjectList(int layerGroup, const wchar_t* listTag)
{
	return Engine::GameManager::GetInstance()->FindObjectList(layerGroup, listTag);
}
Engine::GameObject* FindObject(int layerGroup, const wchar_t* listTag, const wchar_t* objectTag)
{
	return Engine::GameManager::GetInstance()->FindObject(layerGroup, listTag, objectTag);
}
bool AddObjectInLayer(int layerGroup, const wchar_t* listTag, Engine::GameObject* pObject)
{
	return Engine::GameManager::GetInstance()->AddObjectInLayer(layerGroup, listTag, pObject);
}

HWND GetWindow()
{
	return Engine::GameManager::GetInstance()->GetWindow();
}

bool ChangeScene(Engine::Scene* pScene)
{
	return Engine::GameManager::GetInstance()->ChangeScene(pScene);
}

void RemoveAll()
{
	Engine::GameManager::GetInstance()->RemoveAll();
}