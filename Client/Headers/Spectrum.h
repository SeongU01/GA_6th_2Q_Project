#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Animation;
}

class Spectrum : public Engine::MonoBehavior
{
public:
	explicit Spectrum(float interval, const Vector3& drawOffset, const Vector3& size);
private:
	virtual ~Spectrum() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void Reset();
	void SetColor(const XMFLOAT4& useColor, const XMFLOAT4& color);

private:
	XMFLOAT4				_useColor{};
	XMFLOAT4				_color{};
	Engine::Animation*		_pAnimation = nullptr;
	Vector3					_drawOffset;
	Vector3					_size;
	float					_interval = 0.f;
	float					_elapsed = 0.f;	
};

