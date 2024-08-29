#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class Transform;
	class Component abstract : public Base
	{
		friend class GameObject;
	protected:
		explicit Component(const wchar_t* name) { SetName(name); }
		virtual ~Component() = default;

	public:
		virtual void Awake() {}
		virtual void Start() {}
		virtual void FixedUpdate() {}
		virtual void Update(const float& deltaTime) {}
		virtual void LateUpdate(const float& deltaTime) {}
		virtual void Render() {}

	public:
		Transform& GetTransform();
		GameObject& GetOwner();
		_declspec(property(get = GetTransform)) Transform& transform;
		_declspec(property(get = GetOwner)) GameObject& gameObject;

	public:
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args);
	
		template<typename T>
		T* GetComponent();

		template<typename T>
		T* GetComponent(const wchar_t* name);

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
inline T* Engine::Component::GetComponent(const wchar_t* name)
{	
	return _pOwner->GetComponent<T>(name);
}