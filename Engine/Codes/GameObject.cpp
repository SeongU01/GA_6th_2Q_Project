#include "GameObject.h"
#include "TextRenderer.h"
#include "Collider.h"
#include "ICollisionNotify.h"
#include "GameManager.h"

using namespace Engine;

Engine::GameObject::GameObject()
	: _pGameManager(GameManager::GetInstance())
{
	_pTransform = AddComponent<Transform>(L"Transform");
	_pSpriteRenderer = AddComponent<SpriteRenderer>(L"SpriteRenderer");
}

Engine::GameObject::~GameObject()
{
	Free();
}

GameObject* Engine::GameObject::Create()
{
	return new GameObject;
}

void Engine::GameObject::Start()
{
	if (_isFirstInit) return;

	for (auto& component : _components)
		component->Start();

	_isFirstInit = true;
}

void Engine::GameObject::FixedUpdate()
{
	if (!_isFirstInit) return;

	for (auto& component : _components)
		component->FixedUpdate();
}

int Engine::GameObject::Update(const float& deltaTime)
{
	if (!_isFirstInit) return 0;

	for (auto& component : _components)
		component->Update(deltaTime);

	return 0;
}

int Engine::GameObject::LateUpdate(const float& deltaTime)
{
	if (!_isFirstInit) return 0;

	for (auto& component : _components)
		component->LateUpdate(deltaTime);

	_pTransform->UpdateTransform();

	return 0;
}

void Engine::GameObject::AddRenderer()
{
	if (!_isFirstInit) return;

	_pGameManager->AddRenderGroup(_renderGroup, this);
}

void Engine::GameObject::Render()
{
	if (!_isFirstInit || !IsActive()) return;

	if (_isNotAffectCamera)
		_cameraMatrix = D2D1::Matrix3x2F::Identity();

	for (auto& component : _components)
	{
		if (component->IsActive())
			component->Render();
	}

#ifdef _DEBUG
	if (_isDrawCollider)
	{
		for (auto& collider : _colliders)
		{
			if (collider->IsActive())
				_pSpriteRenderer->DrawRect(collider->GetColliderRect());
		}
	}
#endif
}

void Engine::GameObject::OnCollisionEnter(CollisionInfo& info)
{
	for (auto& component : _registeredCollisionEventComponents)
		component->OnCollisionEnter(info);
}

void Engine::GameObject::OnCollision(CollisionInfo& info)
{
	for (auto& component : _registeredCollisionEventComponents)
		component->OnCollision(info);
}

void Engine::GameObject::OnCollisionExit(CollisionInfo& info)
{
	for (auto& component : _registeredCollisionEventComponents)
		component->OnCollisionExit(info);
}

void Engine::GameObject::Free()
{
	for (auto& component : _components)
		SafeRelease(component);
	
	_components.clear();
	_components.shrink_to_fit();
	_colliders.clear();
	_colliders.shrink_to_fit();
}