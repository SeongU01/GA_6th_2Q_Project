#pragma once
#include "Base.h"
#include "Engine_Define.h"

namespace Engine
{
	class GameObject;
	class Collider;
	class CollisionManager : public Base
	{	
	private:
		explicit CollisionManager() = default;
		virtual ~CollisionManager() = default;

	public:
		void CheckCollision(std::list<GameObject*>* src, std::list<GameObject*>* dst);

	private:
		bool IsCollision(Collider* pSrc, Collider* pDst);
		void Free() override;

	public:
		static CollisionManager* Create();
	};
}