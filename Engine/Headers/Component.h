#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class Collider;
	class Component : public Base
	{
		friend class GameObject;
	protected:
		explicit Component() = default;
		virtual ~Component() = default;

	public:
		virtual void Start() = 0;
		virtual void Update(const float& deltaTime) = 0;
		virtual void LateUpdate(const float& deltaTime) = 0;
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
		const char* _name = nullptr;
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