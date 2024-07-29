#pragma once
#include "Base.h"

namespace Engine
{
	class Transform;
	class Timer;
	class Camera : public Base
	{
	private:
		explicit Camera() = default;
		virtual ~Camera() = default;

	public:
		void FixedUpdate();
		void Update(const float& deltaTime);
		void LateUpdate(const float& deltaTime);

	public:
		void SetTarget(Transform* pTarget) { _pTarget = pTarget; }
		void SetOffset(const Vector3& offset) { _offset += offset; }
		void SetMaxPosition(const Vector3& position);
		void SetMinPosition(const Vector3& position) { _minPosition = position; }
		void SetArea(const Vector3& area) { _area = area; }
		void CameraShake(float shakeTime, float shakePower);
		const D2D1_MATRIX_3X2_F& GetCameraMatrix();

	private:
		Vector3 GetRandomShakeVector(const float shakePower);
		// Base을(를) 통해 상속됨
		bool Initialize();
		void Free() override;

	public:
		static Camera* Create();

	private:
		Vector3		_prevPosition;
		Vector3		_offset;
		Vector3		_maxPosition;
		Vector3		_minPosition;
		Vector3		_area;
		Vector3		_shakePosition;
		Transform*	_pTarget = nullptr;
		Transform*	_pTransform = nullptr;
		Timer*		_pTimer = nullptr;
		float		_shakeTime = 0.f;
		float		_shakePower = 0.f;
		float		_originShakePower = 0.f;

		float _shakeElapsedTime = 0.0f;
		Vector3 _previousShakePosition = { 0.f, 0.f, 0.f };
		Vector3 _currentShakePosition = { 0.f, 0.f, 0.f };
		bool _returnToOriginal = false;
	};
}