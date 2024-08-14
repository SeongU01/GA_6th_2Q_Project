#include "CollisionManager.h"
#include "GameObject.h"
#include "Collider.h"

using namespace Engine;

void Engine::CollisionManager::CheckCollision(std::list<GameObject*>* src, std::list<GameObject*>* dst)
{
	for (auto& Src : *src)
	{
		std::vector<Collider*>& srcColliders = Src->GetColliders();
		for (auto Dst : *dst)
		{
			std::vector<Collider*>& dstColliders = Dst->GetColliders();
			for (auto& srcCollider : srcColliders)
			{				
				for (auto& dstCollider : dstColliders)
				{
					if (srcCollider == dstCollider) continue;					

					COLLIDER_ID ID, reverseID;
					ID.leftID = srcCollider->GetID();
					ID.rightID = dstCollider->GetID();

					reverseID.leftID = dstCollider->GetID();
					reverseID.rightID = srcCollider->GetID();

					auto iter = _collisionBuffer.find(ID.ID);
					auto reverseIter = _collisionBuffer.find(reverseID.ID);

					if (iter == _collisionBuffer.end())
					{
						if (reverseIter == _collisionBuffer.end())
						{
							_collisionBuffer.emplace(std::make_pair(ID.ID, false));
							iter = _collisionBuffer.find(ID.ID);
						}
						else
						{
							iter = reverseIter;
						}
					}

					CollisionInfo infoSrc, infoDst;
					infoSrc.itSelf = srcCollider;
					infoSrc.other = dstCollider;
					infoDst.itSelf = dstCollider;
					infoDst.other = srcCollider;

					if (!srcCollider->IsActive() || !dstCollider->IsActive())
					{
						if (iter->second)
						{
							Src->OnCollisionExit(infoSrc);
							Dst->OnCollisionExit(infoDst);
							iter->second = false;
						}

						continue;
					}

					if (IsCollision(srcCollider, dstCollider))
					{						
						if (iter->second)
						{							
							Src->OnCollision(infoSrc);							
							Dst->OnCollision(infoDst);
						}
						else
						{
							Src->OnCollisionEnter(infoSrc);
							Dst->OnCollisionEnter(infoDst);
							iter->second = true;
						}
					}
					else
					{
						if (iter->second)
						{
							Src->OnCollisionExit(infoSrc);
							Dst->OnCollisionExit(infoDst);
							iter->second = false;
						}
					}
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* pSrc, Collider* pDst)
{
	Vector3 radiusSum = (pSrc->GetScale() + pDst->GetScale()) * 0.5f;
	Vector3 distance = XMVectorAbs(pDst->GetPosition() - pSrc->GetPosition());

	if (radiusSum.x >= distance.x && radiusSum.y >= distance.y)
		return true;

	return false;
}

CollisionManager* CollisionManager::Create()
{
	return new CollisionManager;
}

void CollisionManager::Free()
{
	_collisionBuffer.clear();
}
