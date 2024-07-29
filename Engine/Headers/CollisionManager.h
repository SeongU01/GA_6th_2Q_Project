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
		using CollisionBuffer = std::unordered_map<ULONGLONG, bool>;
		union COLLIDER_ID
		{
			struct
			{
				UINT leftID;
				UINT rightID;
			};

			ULONGLONG ID;
		};
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

	private:
		CollisionBuffer _collisionBuffer;
	};
}