#pragma once
#include "Base.h"
namespace Engine
{
	class State : public Base
	{
	protected:
		explicit State() = default;
		virtual ~State() = default;

	public:
		virtual int Update(const float& deltaTime) = 0;
		virtual int LateUpdate(const float& deltaTime) = 0;
		virtual void OnStart() = 0;
		virtual void OnExit() = 0;
		virtual void Reset() {}

	private:
		// Base을(를) 통해 상속됨
		void Free() override;
	};
}
