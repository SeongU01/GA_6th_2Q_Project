#pragma once

#include "Base.h"
#include "Texture.h"
#include "ICollisionNotify.h"

struct CollisionInfo;

namespace Engine
{	
	class Transform;
	class Collider;
	class Component;
	class SpriteRenderer;
	class GameManager;
	
	class GameObject : public Base
	{
		friend class GameManager;
		friend class Layer;
		friend class Component;
		friend class Renderer;
		friend class CollisionManager;
	protected:
		explicit GameObject();
		virtual ~GameObject();
	
	public:
		inline Transform* GetTransform() { return _pTransform; }
		inline std::vector<Collider*>& GetColliders() { return _colliders; }
		inline bool IsDead() const { return _isDead; }

		inline void SetDead() { _isDead = true; }
		inline void SetDontDestroyObject(bool isActive) { _dontDestroy = isActive; }
		inline void SetRenderGroup(int renderGroup) { _renderGroup = renderGroup; }

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

		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			T* pComponent = new T(std::forward<Args>(args)...);
			pComponent->_pOwner = this;
			pComponent->Awake();
			_components.push_back(pComponent);

			if constexpr (std::is_base_of_v<ICollisionNotify, T>)
				_registeredCollisionEventComponents.push_back(pComponent);

			if constexpr (std::is_base_of_v<Collider, T>)
				_colliders.push_back(pComponent);
			
			return pComponent;
		}

	public:
		static GameObject* Create();

	private:
		void Start();
		void FixedUpdate();
		int Update(const float& deltaTime);
		int LateUpdate(const float& deltaTime);
		void AddRenderer();
		void Render();
		void OnCollisionEnter(CollisionInfo& info);
		void OnCollision(CollisionInfo& info);
		void OnCollisionExit(CollisionInfo& info);

	private:
		void Free() override;
	
	private:
		std::vector<Component*>			_components;
		std::vector<Collider*>			_colliders;
		std::vector<ICollisionNotify*>	_registeredCollisionEventComponents;
		GameManager*					_pGameManager = nullptr;
		int								_renderGroup = -1;
		bool							_isDead = false;
		bool							_dontDestroy = false;
		bool							_isFirstInit = false;

	protected:
		Transform*						_pTransform	= nullptr;
		SpriteRenderer*					_pSpriteRenderer = nullptr;

#ifdef _DEBUG
		bool _isDrawCollider = false;
#endif
	};	
}

#include "Transform.h"
#include "SpriteRenderer.h"
#include "Collider.h"