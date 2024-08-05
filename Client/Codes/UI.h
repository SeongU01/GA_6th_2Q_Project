#pragma once
#include "MonoBehavior.h"
//이벤트핸들러추가.
namespace Engine
{
	class Animation;
}

class UI : public Engine::GameObject
{
public:
	struct UIInfo
	{
		Vector3 position;
		Vector3 scale{ 1.f, 1.f, 0.f };
		Engine::Transform* pParent = nullptr;
		const wchar_t* textureTag = nullptr;
		const char* name = nullptr;
		float aniSpeed = 0.f;
		int fixFrame = 0;
		bool isFixFrame = false;
	};

private:
	explicit UI() = default;
	virtual ~UI() = default;

public:
	const Vector3& GetOriginScale() { return _originScale; }
	const D2D1_SIZE_F& GetImageSize();
	void SetPosition(const Vector3& position);
	void SetOffsetPosition(const Vector3& position);
	void SetScale(const Vector3& scale);
	void SetScaleRate(float rate);
	void SetRotation(float angle);
	void SetFixFrame(bool isActive, int fixFrame);
	void AddRotation(float angle);
	void AddScale(const Vector3& scale);
private:
	void Initialize(UIInfo& info);
	void Free() override;

public:
	static UI* Create(UIInfo& info);

private:
	UIInfo				_info;
	Vector3				_originScale;
	Vector3				_offsetPosition;
	D2D1_SIZE_F			_imageSize;
	Engine::Animation* _pAnimation = nullptr;
	float				_rotation = 0.f;
	float				_scaleRate = 1.f;
};

