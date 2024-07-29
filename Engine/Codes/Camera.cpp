#include "Camera.h"
#include "Transform.h"
#include "Timer.h"

using namespace Engine;

// Lerp �Լ�
Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
{
	return {
		a.x + t * (b.x - a.x),
		a.y + t * (b.y - a.y),
		a.z + t * (b.z - a.z)
	};
}

void Engine::Camera::FixedUpdate()
{	
}

void Engine::Camera::Update(const float& deltaTime)
{
	_pTimer->Update(deltaTime);

	if (nullptr != _pTarget)
	{
		_pTransform->SetPosition(_pTarget->GetPosition());
	}
}

void Engine::Camera::LateUpdate(const float& deltaTime)
{	
	Vector3 position = _pTransform->GetPosition();
	Vector3 max = _maxPosition;
	Vector3 area = _area * 0.5f;

	if (position.x + area.x >= max.x)
		position.x = max.x - area.x;

	if (position.y + area.y >= max.y)
		position.y = max.y - area.y;

	if (0.f > position.x - area.x) position.x = area.x;
	if (0.f > position.y - area.y) position.y = area.y;
	
	if ((*_pTimer)[0].isActive)
	{
		_shakeElapsedTime += deltaTime;

		// �ֱ������� ���ο� ������ ��鸲 ���� ����
		if (static_cast<int>(_shakeElapsedTime * 5) % 2 == 0) // ��: 0.05�ʸ��� ����
		{
			_currentShakePosition = GetRandomShakeVector(_shakePower);
		}

		// ���� �����Ӱ��� ���� ����
		_shakePosition = Lerp(_previousShakePosition, _currentShakePosition, deltaTime * 10.0f); // ���� �ӵ� ����

		// ���� ��ġ�� ���� ��ġ�� ������Ʈ
		_previousShakePosition = _shakePosition;

		_shakePower -= _originShakePower * deltaTime / _shakeTime;
	}

	if (_pTimer->IsOverTime(0, _shakeTime))
	{
		_originShakePower = 0.f;
		_shakePower = 0.f;
		_shakeTime = 0.f;
		_pTimer->SetActive(0, false);
		_shakeElapsedTime = 0.0f;
		_previousShakePosition = { 0.f, 0.f, 0.f };
		_returnToOriginal = true; // ���� �ڸ��� ���ư��� ����
	}

	// ��鸲 �� ���� �ڸ��� �ε巴�� ����
	if (_returnToOriginal)
	{
		_shakePosition = Lerp(_shakePosition, { 0.f, 0.f, 0.f }, deltaTime * 5.0f); // ���� �ӵ� ����
		if (fabs(_shakePosition.x) < 0.01f && fabs(_shakePosition.y) < 0.01f)
		{
			_shakePosition = { 0.f, 0.f, 0.f };
			_returnToOriginal = false; // ���� �ڸ��� ���ƿ��� ���� �Ϸ�
		}
	}

	_pTransform->SetPosition(position - _offset + _shakePosition);
	_pTransform->Update(0.f);
}

void Engine::Camera::SetMaxPosition(const Vector3& position)
{
	_maxPosition = position;
	_offset = _area * 0.5f;
}

void Engine::Camera::CameraShake(float shakeTime, float shakePower)
{
	if ((*_pTimer)[0].isActive)
		return;

	_shakeTime = shakeTime;
	_originShakePower = _shakePower = shakePower;
	_pTimer->SetActive(0, true);
	_prevPosition = _pTransform->GetPosition();
}

const D2D1_MATRIX_3X2_F& Engine::Camera::GetCameraMatrix()
{
	return _pTransform->GetWorldMatrix();
}

Vector3 Engine::Camera::GetRandomShakeVector(const float shakePower)
{
	float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.141592f;
	return { cos(angle) * shakePower, sin(angle) * shakePower, 0.f };
}

bool Engine::Camera::Initialize()
{
	_pTransform = new Transform("Transform");
	_pTimer = new Timer("Timer");
	_pTimer->Initialize(1);

	return true;
}

void Engine::Camera::Free()
{
	SafeRelease(_pTransform);
	SafeRelease(_pTimer);
}

Camera* Engine::Camera::Create()
{
	Camera* pInstance = new Camera;
	if (pInstance->Initialize())
		return pInstance;

	SafeRelease(pInstance);
	return nullptr;
}