#pragma once

void SetSlowTime(float rate, float time)
{
	Engine::GameManager::GetInstance()->SetSlowTime(rate, time);
}