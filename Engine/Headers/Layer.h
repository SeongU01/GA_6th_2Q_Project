#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class Layer : public Base
	{
		using ObjectData = std::unordered_map<const wchar_t*, std::list<GameObject*>>;
	private:
		explicit Layer() = default;
		virtual ~Layer() = default;

	public:
		void Start();
		void FixUpdate();
		int Update(const float& deltaTime);
		int LateUpdate(const float& deltaTime);
		void AddRenderer();

		std::list<GameObject*>* FindObjectList(const wchar_t* listTag) { return &_objectData[listTag]; }
		GameObject* FindObject(const wchar_t* listTag, const wchar_t* objectTag);
		bool AddObject(const wchar_t* listTag, GameObject* pObject);
		void ClearObjectList(const wchar_t* listTag);
		void ClearAllObjectList();
		void RemoveAll();

	private:
		void Free() override;

	public:
		static Layer* Create();

	private:
		ObjectData _objectData;
	};
}