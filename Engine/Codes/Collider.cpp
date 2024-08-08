#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"

using namespace Engine;

_uint Collider::g_ID = 0;

Engine::Collider::Collider(const wchar_t* name)
	: Component(name), _ID(g_ID++)
{
}

void Engine::Collider::LateUpdate(const float& deltaTime)
{
	_position = XMVector3TransformCoord(_offset, XMLoadFloat4x4(&transform.xmWorldMatrix));
	_scale = _originScale * transform.scale;
}

#ifdef _DEBUG
D2D1_RECT_F Engine::Collider::GetColliderRect() const
{
	D2D1_RECT_F rect{};
	rect.left = -_originScale.x * 0.5f;
	rect.right = _originScale.x * 0.5f;
	rect.top = -_originScale.y * 0.5f;
	rect.bottom = _originScale.y * 0.5f;

	return rect;
}
#endif

void Engine::Collider::Free()
{
}