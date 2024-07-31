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
				if (!srcCollider->IsActive()) continue;

				for (auto& dstCollider : dstColliders)
				{
					if (srcCollider == dstCollider) continue;
					if (!dstCollider->IsActive()) continue;

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
	float fRadiusSumX = float(int(pSrc->GetScale().x + pDst->GetScale().x) >> 1);
	float fRadiusSumY = float(int(pSrc->GetScale().y + pDst->GetScale().y) >> 1);

	float fDistX = fabs(pDst->GetPosition().x - pSrc->GetPosition().x);
	float fDistY = fabs(pDst->GetPosition().y - pSrc->GetPosition().y);

	if (fRadiusSumX >= fDistX && fRadiusSumY >= fDistY)
	{
		return true;
	}

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
