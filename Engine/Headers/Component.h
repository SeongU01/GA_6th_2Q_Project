#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class Collider;
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

	protected:
		template <typename T>
		T* AddComponent(const char* name);
	
		template<typename T>
		T* GetComponent();

		template<typename T>
		T* GetComponent(const char* name);

		template<>
		Collider* GetComponent(const char* name);

		// Base을(를) 통해 상속됨
		void Free() = 0;

	protected:
		GameObject* _pOwner = nullptr;
	};
}

#include "GameObject.h"
template<typename T>
inline T* Engine::Component::AddComponent(const char* name)
{
	return _pOwner->AddComponent<T>(name);
}

template<typename T>
inline T* Engine::Component::GetComponent()
{
	return _pOwner->GetComponent<T>();
}

template<typename T>
inline T* Engine::Component::GetComponent(const char* name)
{	
	return _pOwner->GetComponent(name);
}

template<>
inline Engine::Collider* Engine::Component::GetComponent(const char* name)
{
	return _pOwner->GetComponent<Collider>(name);
}