#pragma once

void SetSumTime(float time)
{
	Engine::TimeManager::GetInstance()->SetSumTime(time);
}

void SetSlowTime(float rate)
{
	Engine::TimeManager::GetInstance()->SetSlowTime(rate);
}

double GetSumTime()
{ 
	return Engine::TimeManager::GetInstance()->GetSumTime();
}

float GetDeltaTime() 
{ 
	return Engine::TimeManager::GetInstance()->GetDeltaTime();
}

bool FrameLock(float frame)
{
	return Engine::TimeManager::GetInstance()->FrameLock(frame);
};

