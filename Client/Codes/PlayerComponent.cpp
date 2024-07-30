#include "PlayerComponent.h"
#include "Client_Define.h"

void PlayerComponent::Start()
{
}

void PlayerComponent::OnCollisionEnter(CollisionInfo& info)
{
	if (*info.other->GetOwner() == "Slime")
	{
		if (*info.other == "Head")
		{
			if (*info.itSelf == "Foot")
			{
				// 머리를 밟은거에 대한 정의
				info.other->GetOwner()->SetDead();
			}
		}
	}
}

void PlayerComponent::OnCollision(CollisionInfo& info)
{
}

void PlayerComponent::OnCollisionExit(CollisionInfo& info)
{
}

void PlayerComponent::Free()
{
}
