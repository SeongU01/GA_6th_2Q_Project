#pragma once
#include "GameManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

namespace Engine
{
	// Layer
	inline void ClearLayer(int layerGroup);
	inline void ClearObjectList(int layerGroup, const wchar_t* listTag);	
	inline std::list<GameObject*>* FindObjectList(int layerGroup, const wchar_t* listTag);
	inline GameObject* FindObject(int layerGroup, const wchar_t* listTag, const wchar_t* objectTag);
	inline bool AddObjectInLayer(int layerGroup, const wchar_t* listTag, GameObject* pObject);
	inline HWND GetWindow();
	inline bool ChangeScene(Engine::Scene* pScene);
	inline void RemoveAll();
	#include "Export.inl"
}

namespace Camera
{
	// Camera
	inline void CameraShake(float shakeTime, float shakePower);
	inline void SetTarget(Engine::Transform* pTarget);
	inline void SetOffset(const Vector3& offset);
	inline void SetMaxPosition(const Vector3& position);
	inline void SetMinPosition(const Vector3& position);
	inline void SetArea(const Vector3& area);
	#include "Export_Camera.inl"
}

namespace Resource
{	// ResourceMgr
	inline Engine::Texture* FindTexture(const wchar_t* textureTag);
	#include "Export_Resource.inl"
}
namespace Time
{
	// TimeMgr
	inline double GetSumTime();
	inline float GetGlobalDeltaTime();
	inline void SetSumTime(float time);
	inline void SetSlowTime(float rate);
	inline void SetSlowTime(float rate, float duration);
	inline float GetDeltaTime();
	#include "Export_Time.inl"
}

namespace Input
{
	// InputMgr
	inline bool IsKeyDown(_byte keycord);
	inline bool IsKeyDown(Input::MouseState mouseState);
	inline bool IsKeyDown(Input::PadState padState);
	inline bool IsKeyUp(_byte keycord);
	inline bool IsKeyUp(Input::MouseState mouseState);
	inline bool IsKeyUp(Input::PadState padState);
	inline bool IsKeyPress(_byte keycord);
	inline bool IsKeyPress(Input::MouseState mouseState);
	inline bool IsKeyPress(Input::PadState padState);
	inline float GetAxis(Input::Axis type);
	inline float GetMouseMove(Input::MouseMove mouseMove);
	inline bool IsMouseWheel(Input::MouseState mouseState);
	inline void SetThumbDeadZone(short left, short right);
	inline void SetTriggerThreshold(byte value);
	inline void SetVibration(float power);
	#include "Export_Input.inl"
}

namespace Sound
{
	// SoundMgr
	inline FMOD::Channel* PlaySound(const char* soundTag, int channelID, float volume, bool isLoop);
	inline void DistancePlaySound(const Vector3& position, const char* soundTag, int groupID, bool isLoop);
	inline void SetFadeVolume(int groupID, float volume);
	inline void SetVolume(int groupID, float volume);
	inline void StopSound(int groupID);
	inline void SetSoundTarget(Engine::GameObject* pTarget);
	inline void PauseSound(int groupID, bool isPause);
	#include "Export_Sound.inl"
}