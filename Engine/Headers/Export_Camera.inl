#pragma once


// Camera
void CameraShake(float shakeTime, float shakePower)
{
	Engine::GameManager::GetInstance()->CameraShake(shakeTime, shakePower);
}

void SetTarget(Engine::Transform* pTarget)
{
	Engine::GameManager::GetInstance()->SetCameraTarget(pTarget);
}
void SetOffset(const Vector3& offset)
{
	Engine::GameManager::GetInstance()->SetCameraOffset(offset);
}
void SetMaxPosition(const Vector3& position)
{
	Engine::GameManager::GetInstance()->SetCameraMaxPosition(position);
}
void SetMinPosition(const Vector3& position)
{
	Engine::GameManager::GetInstance()->SetCameraMinPosition(position);
}
void SetArea(const Vector3& area)
{
	Engine::GameManager::GetInstance()->SetCameraArea(area);
}