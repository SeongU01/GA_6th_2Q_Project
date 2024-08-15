#pragma once
#include "Component.h"

namespace Engine
{
	class EventInvoker : public Component
	{
		struct EventAction
		{
			EventAction(const std::function<void()>& func, float activeTime)
				: function(func), activeTime(activeTime) {}

			std::function<void()> function = nullptr;
			float elapsed = 0.f;
			float activeTime = 0.f;
		};
	public:
		explicit EventInvoker(const wchar_t* name);
	private:
		virtual ~EventInvoker() = default;

	public:
		void Update(const float& deltaTime) override;
		void SetUseGlobalDeltaTime(bool isActive) { _isUseGlobalDeltaTime = isActive; }
		void ResetAction() { _eventActions.clear(); }
		void BindAction(const float activeTime, const std::function<void()>& function)
		{
			_eventActions.push_back(EventAction(function, activeTime));
		}
	private:
		// Component을(를) 통해 상속됨
		void Free() override;

	private:
		std::list<EventAction>	_eventActions;
		bool					_isUseGlobalDeltaTime = false;

	};
}