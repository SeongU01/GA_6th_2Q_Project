#pragma once

#include "Base.h"

namespace Engine
{
	// Scene
	class Layer;
	class Scene;
	class SceneManager;

	// System
	class InputManager;
	class TimeManager;
	class GraphicManager;

	// Resource
	class Texture;
	class ResourceManager;
	class SoundManager;

	// Util
	class GameObject;
	class Renderer;
	class Camera;
	class InputAction;
	class Transform;

	// App
	class WinApp;

	class GameManager : public Base, public SingleTon<GameManager>
	{
		friend class SingleTon;
	public:
		struct GameDefaultSetting
		{
			HINSTANCE hInstance{};
			const TCHAR* appName{};
			int renderGroupSize{};
			int maxSoundGroup{};
			int layerSize{};
			int width{};
			int height{};
			int fiexedCount = 50;
			bool isFullScreen = false;
		};
	private:
		explicit GameManager();
		virtual ~GameManager() = default;
		NOCOPY(GameManager)

	public:
		void Run();
		bool Initialize(const GameDefaultSetting& info);

		// TimeMgr
		void SetSlowTime(float rate);

		// SceneMgr
		bool ChagneScene(Scene* pScene);
		void ClearObjectList(int layerGroup, const char* listTag);
		void ClearLayer(int layerGroup);
		std::list<GameObject*>* FindObjectList(int layerGroup, const char* listTag);
		GameObject* FindObject(int layerGroup, const char* listTag, const char* objectTag);
		bool AddObjectInLayer(int layerGroup, const char* listTag, GameObject* pObject);

		// SoundMgr
		void LoadSound(const char* filePath);

		// Renderer
		bool AddRenderGroup(int renderGroup, GameObject* pObject);
		void SetSortGroup(int sortGroup, bool(*sortFunc)(GameObject*, GameObject*));
		size_t GetUsedVRAM();

		// Camera
		void SetCameraTarget(Transform* pTransform);
		void SetCameraOffset(const Vector3& offset);
		void SetCameraMaxPosition(const Vector3& position);
		void SetCameraMinPosition(const Vector3& position);
		void SetCameraArea(const Vector3& area);
		void CameraShake(float shakeTime, float shakePower);
		Camera* GetCurrCamera();

	private:
		void StartGame();
		void FixedUpdateGame(int count);
		int UpdateGame();
		int LateUpdateGame();
		void RenderGame();
		// Base��(��) ���� ��ӵ�
		void Free() override;

	private:
		WinApp* _pWinApp = nullptr;

		InputManager*		_pInputMgr		= nullptr;
		TimeManager*		_pTimeMgr		= nullptr;
		ResourceManager*	_pResourceMgr	= nullptr;
		SoundManager*		_pSoundMgr		= nullptr;
		GraphicManager*		_pGraphicMgr	= nullptr;
		SceneManager*		_pSceneMgr		= nullptr;

		Renderer*			_pRenderer		= nullptr;
		HWND				_hWnd			= nullptr;
		GameObject*			_pSoundTarget	= nullptr;
		Camera*				_pCamera		= nullptr;
		float				_elapsed		= 0.f;
		int					_fixedCount = 0;
		bool				_isSceneChange	= false;
	};
}