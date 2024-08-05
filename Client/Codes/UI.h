#pragma once
#include "MonoBehavior.h"

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
	};

private:
	explicit UI() = default;
	virtual ~UI() = default;

public:
	const D2D1_SIZE_F& GetImageSize();
	void SetPosition(const Vector3& position);
	void SetScale(const Vector3& scale);
	void SetScaleRate(float rate);
	void SetRotation(float angle);
	void AddRotation(float angle);
	void AddScale(const Vector3& scale);
private:
	void Initialize(UIInfo& info);
	void Free() override;

public:
	static UI* Create(UIInfo& info);

private:
	UIInfo				_info;
	D2D1_SIZE_F			_imageSize;
	float				_rotation = 0.f;
	float				_scaleRate = 1.f;
};

