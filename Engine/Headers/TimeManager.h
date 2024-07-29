#pragma once

#include "Base.h"

namespace Engine
{
	class TimeManager : public Base
	{
	private:
		explicit TimeManager() = default;
		virtual ~TimeManager() = default;

	public:
		void SetSlowTime(float rate, float time);
		float GetDeltaTime() { return 100 <= _deltaTime ? 0.001f : _deltaTime * 0.001f * _slowRate; }
		void Update();
		bool FrameLock(float frame);

	private:
		bool Initialize();

	private:		
		_ullong _currTime;
		_ullong _oldTime;
		_ullong _deltaTime;
		_ullong _globalDeltaTime;
		_ullong _fixTime;
		_ullong _fixFrame;
		_ullong	_elapsed;
		_ullong	_slowTime;
		float	_slowRate = 1.f;

	private:
		// CBase을(를) 통해 상속됨
		void Free() override;

	public:
		static TimeManager* Create();
	};
}