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
				// �Ӹ��� �����ſ� ���� ����
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
