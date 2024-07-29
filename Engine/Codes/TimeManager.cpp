#include "TimeManager.h"

using namespace Engine;

bool TimeManager::Initialize()
{
	_oldTime = GetTickCount64();
	_currTime = GetTickCount64(); 

	return true;
}

TimeManager* TimeManager::Create()
{
	TimeManager* pInstance = new TimeManager;

	if (pInstance->Initialize())
		return pInstance;

	SafeRelease(pInstance);
	return nullptr;
}

void Engine::TimeManager::SetSlowTime(float rate, float time)
{
	_elapsed = 0;
	_slowRate = rate;
	_slowTime = _ullong(time * 1000); 
}

void TimeManager::Update()
{
	_oldTime = _currTime;
	_currTime = GetTickCount64();
	_deltaTime = _currTime - _oldTime;
	_globalDeltaTime = _deltaTime;

	_elapsed += _globalDeltaTime;

	if (_elapsed >= _slowTime) _slowRate = 1.f;
}

bool TimeManager::FrameLock(float frame)
{
	_fixTime = _deltaTime;
	_fixFrame = _ullong(1000 / frame);

	if (_fixFrame <= _fixTime)
	{
		_fixTime = 0;
		return true;
	}

	return false;
}

void TimeManager::Free()
{
}
