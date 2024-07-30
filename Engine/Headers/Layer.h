#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class Layer : public Base
	{
		using ObjectData = std::unordered_map<const char*, std::list<GameObject*>>;
	private:
		explicit Layer() = default;
		virtual ~Layer() = default;

	public:
		void Start();
		void FixUpdate();
		int Update(const float& deltaTime);
		int LateUpdate(const float& deltaTime);
		void AddRenderer();

		std::list<GameObject*>* FindObjectList(const char* listTag) { return &_objectData[listTag]; }
		GameObject* FindObject(const char* listTag, const char* objectTag);
		bool AddObject(const char* listTag, GameObject* pObject);
		void ClearObjectList(const char* listTag);
		void ClearAllObjectList();

	private:
		void Free() override;

	public:
		static Layer* Create();

	private:
		ObjectData _objectData;
	};
}