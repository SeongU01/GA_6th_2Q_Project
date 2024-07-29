#pragma once

#include "Base.h"

namespace Engine
{
	class Scene abstract : public Base
	{
	protected:
		explicit Scene() = default;
		virtual ~Scene() = default;

	public:
		virtual int Update(const float& deltaTime) = 0;
		virtual int LateUpdate(const float& deltaTime) = 0;
		virtual bool Initialize() = 0;
	};
}