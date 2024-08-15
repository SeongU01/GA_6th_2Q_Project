#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"

using namespace Engine;

Engine::Collider::Collider(const wchar_t* name)
	: Component(name)
{
}

void Engine::Collider::LateUpdate(const float& deltaTime)
{
	_position = XMVector3TransformCoord(_offset, XMLoadFloat4x4(&transform.xmWorldMatrix));
	_scale = XMVectorAbs(_originScale * transform.scale);

	if (!IsActive())
	{
		for (auto& collider : _collidedOthers)
		{
			CollisionInfo info;
			info.itSelf = collider;
			info.other = this;
			collider->EraseOther(this);

			gameObject.OnCollisionExit(info);
			collider->gameObject.OnCollisionExit(info);
		}

		_collidedOthers.clear();
	}
}

#ifdef _DEBUG
D2D1_RECT_F Engine::Collider::GetColliderRect() const
{
	D2D1_RECT_F rect{};
	rect.left = _offset.x - _originScale.x * 0.5f;
	rect.right = _offset.x + _originScale.x * 0.5f;
	rect.top = _offset.y - _originScale.y * 0.5f;
	rect.bottom = _offset.y + _originScale.y * 0.5f;

	return rect;
}
#endif

void Engine::Collider::InsertOther(Collider* pCollider)
{
	_collidedOthers.insert(pCollider);
}

void Engine::Collider::EraseOther(Collider* pCollider)
{
	_collidedOthers.erase(pCollider);
}

bool Engine::Collider::FindOther(Collider* pCollider)
{
	auto iter = _collidedOthers.find(pCollider);
	
	return iter != _collidedOthers.end();
}

void Engine::Collider::Free()
{
	for (auto& collider : _collidedOthers)
	{
		collider->EraseOther(this);
	}
}