#pragma once
// SceneMgr
bool ChagneScene(Engine::Scene* pScene)
{
	return Engine::GameManager::GetInstance()->ChangeScene(pScene);
}