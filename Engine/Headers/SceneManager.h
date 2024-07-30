#pragma once
#include "Base.h"

namespace Engine
{
	class Scene;
	class Layer;
	class GameObject;
	class SceneManager : public Base
	{
	private:
		explicit SceneManager() = default;
		virtual ~SceneManager() = default;

	public:
		void Start();
		void FixedUpdate();
		int Update(const float& deltaTime);
		int LateUpdate(const float& deltaTime);
		void AddRenderGroup();

		bool SetUpLayer(int layerSize);
		bool ChangeScene(Scene* pScene);
		void ClearObjectList(int layerGroup, const char* listTag);
		void ClearLayer(int layerGroup);
		std::list<GameObject*>* FindObjectList(int layerGroup, const char* listTag);
		GameObject* FindObject(int layerGroup, const char* listTag, const char* objectTag);
		bool AddObjectInLayer(int layerGroup, const char* listTag, GameObject* pObject);

	private:
		// Base을(를) 통해 상속됨
		void Free() override;

	public:
		static SceneManager* Create();

	private:
		std::vector<Layer*> _layers;
		Scene*	_pScene = nullptr;
		bool	_isSetUp = false;
	};
}

