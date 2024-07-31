#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class Collider;
	class Transform;
	class Component abstract : public Base
	{
		friend class GameObject;
	protected:
		explicit Component(const char* name) { SetName(name); }
		virtual ~Component() = default;

	public:
		virtual void Awake() {}
		virtual void Start() {}
		virtual void FixedUpdate() {}
		virtual void Update(const float& deltaTime) {}
		virtual void LateUpdate(const float& deltaTime) {}
		virtual void Render() {}

	public:
		Transform* GetTransform();
		_declspec(property(get = GetTransform)) Transform* transform;

	protected:
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);
	
		template<typename T>
		T* GetComponent();

		template<typename T>
		T* GetComponent(const char* name);

		// Base을(를) 통해 상속됨
		void Free() = 0;

	protected:
		GameObject* _pOwner = nullptr;
	};
}

#include "GameObject.h"
template <typename T, typename... Args>
inline T* Engine::Component::AddComponent(Args&&... args)
{
	return _pOwner->AddComponent<T>(std::forward<Args>(args)...);
}

template<typename T>
inline T* Engine::Component::GetComponent()
{
	return _pOwner->GetComponent<T>();
}

template<typename T>
inline T* Engine::Component::GetComponent(const char* name)
{	
	return _pOwner->GetComponent<T>(name);
}