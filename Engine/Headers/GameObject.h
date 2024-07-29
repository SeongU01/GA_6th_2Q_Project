#pragma once

#include "Base.h"
#include "Texture.h"

namespace Engine
{	
	class Transform;
	class Collider;
	class Component;
	class SpriteRenderer;
	class GameObject : public Base
	{
		friend class GameManager;
		friend class Layer;
		friend class Component;
		friend class Renderer;

	protected:
		explicit GameObject();
		virtual ~GameObject();

	public:
		void FixedUpdate();
		int Update(const float& deltaTime);
		int LateUpdate(const float& deltaTime);
		void Render();
		void OnCollision(CollisionInfo& info) {}
		void OnCollisionEnter(CollisionInfo& info) {}
		void OnCollisionExit(CollisionInfo& info) {}

	public:
		bool operator==(const char* str)
		{
			if (nullptr == _name) return false;
			return !strcmp(_name, str);
		}
		bool operator!=(const char* str)
		{ 
			if (nullptr == _name) return false;
			return strcmp(_name, str); 
		}

		Transform* GetTransform() { return _pTransform; }
		std::vector<Collider*>& GetColliders() { return _colliders; }
		bool IsDead() const { return _isDead; }		

		void SetDead() { _isDead = true; }
		void SetDontDestroyObject(bool isActive) { _dontDestroy = isActive; }

		template<typename T>
		T* GetComponent(const char* name)
		{
			for (auto& component : _components)
			{
				if (!strcmp(component->GetName(), name))
					return static_cast<T*>(component);
			}

			return nullptr;
		}

		template <>
		Collider* GetComponent(const char* name);

		template<typename T>
		T* GetComponent()
		{
			for (auto& component : _components)
			{
				if (typeid(*component) == typeid(T))					
					return static_cast<T*>(component);
			}

			return nullptr;
		}

	protected:
		template<typename T>
		T* AddComponent(const char* name)
		{
			T* pComponent = new T(name);
			pComponent->_pOwner = this;
			_components.push_back(pComponent);

			return pComponent;
		}

		template <>
		Collider* AddComponent(const char* name);

	public:
		static GameObject* Create();

	private:
		void Free() override;
	
	private:
		std::vector<Component*>	_components;
		std::vector<Collider*>	_colliders;
		bool					_isDead = false;
		bool					_dontDestroy = false;

	protected:
		std::vector<Texture*>	_textures;
		Transform*				_pTransform	= nullptr;
		SpriteRenderer*			_pSpriteRenderer = nullptr;

#ifdef _DEBUG
		bool _isDrawCollider = false;
#endif
	};	
}

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Collider.h"