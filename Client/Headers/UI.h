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
		const wchar_t* name = nullptr;
		int fixFrame = 0;
	};

private:
	explicit UI() = default;
	virtual ~UI() = default;

public:
	const Vector3& GetOriginScale() { return _originScale; }
	const D2D1_SIZE_F& GetImageSize();
	const D2D1_SIZE_F& GetSize();
	void SetFrame(int index);
	void SetPosition(const Vector3& position);
	void SetOffsetPosition(const Vector3& position);
	void SetScale(const Vector3& scale);
	void SetScaleRate(float rate);
	void SetRotation(float angle);
	void AddRotation(float angle);
	void AddScale(const Vector3& scale);

private:
	void Initialize(const UIInfo& info);
	void Free() override;

public:
	static UI* Create(const UIInfo& info);

private:
	UIInfo				_info;

	Vector3				_originScale;
	Vector3				_offsetPosition;
	D2D1_SIZE_F			_imageSize;    
	D2D1_SIZE_F			_realSize;
	float				_rotation = 0.f;
	float				_scaleRate = 1.f;
};

