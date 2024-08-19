#pragma once

void SetSumTime(float time)
{
	Engine::TimeManager::GetInstance()->SetSumTime(time);
}

void SetSlowTime(float rate)
{
	Engine::TimeManager::GetInstance()->SetSlowTime(rate);
}

void SetSlowTime(float rate, float duration)
{
	Engine::TimeManager::GetInstance()->SetSlowTime(rate, duration);
}

float GetGlobalDeltaTime()
{
	return Engine::TimeManager::GetInstance()->GetGlobalDeltaTime();
}

double GetSumTime()
{ 
	return Engine::TimeManager::GetInstance()->GetSumTime();
}

float GetDeltaTime() 
{ 
	return Engine::TimeManager::GetInstance()->GetDeltaTime();
}

