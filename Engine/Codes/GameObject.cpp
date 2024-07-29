#include "GameObject.h"

using namespace Engine;

Engine::GameObject::GameObject()
{
	_pTransform = AddComponent<Transform>("Transform");
	_pSpriteRenderer = AddComponent<SpriteRenderer>("SpriteRenderer");
	_pSpriteRenderer->_pTransform = _pTransform;	
}

Engine::GameObject::~GameObject()
{
	Free();
}

void Engine::GameObject::FixedUpdate()
{
}

int Engine::GameObject::Update(const float& deltaTime)
{
	for (auto& component : _components)
		component->Update(deltaTime);	

	return 0;
}

int Engine::GameObject::LateUpdate(const float& deltaTime)
{
	for (auto& component : _components)
		component->LateUpdate(deltaTime);

	for (auto& collider : _colliders)
		collider->Update(0.f);

	return 0;
}

void Engine::GameObject::Render()
{
	if (!_isLateInit)
		return;

	for (auto& component : _components)
	{
		if (component->_isActive)
			component->Render();
	}

#ifdef _DEBUG
	if (_isDrawCollider)
	{
		for (auto& collider : _colliders)
			_pSpriteRenderer->DrawRect(collider->GetColliderRect());
	}
#endif
}

GameObject* Engine::GameObject::Create()
{
	return new GameObject;
}

void Engine::GameObject::Free()
{
	for (auto& component : _components)
		SafeRelease(component);

	for (auto& collider : _colliders)
		SafeRelease(collider);
	
	_textures.clear();
	_textures.shrink_to_fit();
	_components.clear();
	_components.shrink_to_fit();
	_colliders.clear();
}

template <>
Engine::Collider* Engine::GameObject::GetComponent(const char* name)
{
	for (auto& collider : _colliders)
	{
		if (!strcmp(collider->_name, name))
			return collider;
	}

	return nullptr;
}

template <>
Engine::Collider* Engine::GameObject::AddComponent(const char* name)
{
	Collider* pCollider = new Collider(name);
	pCollider->_pOwner = this;
	pCollider->_pTransform = _pTransform;
	_colliders.push_back(pCollider);

	return pCollider;
}