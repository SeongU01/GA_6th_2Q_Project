#pragma once
#include "Component.h"
#include <functional>

namespace Engine
{
	class EventInvoker : public Component
	{
		using EventFunction = std::function<void()>;
		struct EventAction
		{
			EventAction(EventFunction func, float activeTime)
				: function(func), activeTime(activeTime) {}

			EventFunction function = nullptr;
			float elapsed = 0.f;
			float activeTime = 0.f;
		};
	public:
		explicit EventInvoker(const char* name) { _name = name; }
	private:
		virtual ~EventInvoker() = default;

	public:
		void Update(const float& deltaTime) override;
		void ResetAction() { _eventActions.clear(); }
		template <typename T>
		void BindAction(const float activeTime, T* instance, void (T::*function)())
		{
			auto effect = [instance, function]()-> void
				{
					(instance->*function)();
				};

			_eventActions.push_back(EventAction(effect, activeTime));
		}
	private:
		// Component을(를) 통해 상속됨
		void Free() override;

	private:
		std::list<EventAction> _eventActions;
	};
}