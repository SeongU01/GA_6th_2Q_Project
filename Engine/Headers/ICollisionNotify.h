#pragma once

namespace Engine
{
	class ICollisionNotify
	{
	public:
		virtual void OnCollisionEnter(CollisionInfo& info) = 0;
		virtual void OnCollision(CollisionInfo& info) = 0;
		virtual void OnCollisionExit(CollisionInfo& info) = 0;
	};
}