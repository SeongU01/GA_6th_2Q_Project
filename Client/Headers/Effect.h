#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Animation;
	class SpriteRenderer;
}
enum class RenderGroup;
class Effect : public Engine::MonoBehavior
{
public:
	struct EffectInfo
	{
		Vector3 position{};
		Vector3 scale = { 1.f, 1.f, 1.f };
		Vector3 direction{};
		Vector3 drawOffset{};
		Engine::Transform* pTarget = nullptr;
		const wchar_t* textureTag = nullptr;
		ID2D1Bitmap* pBitmap = nullptr;
		RenderGroup renderGroup;
		float life = 1.f;
		float speed = 0.f;
		float aniSpeed = 0.f;
		float rotation = 0.f;
		float fadeSpeed = 0.f;
		int fixFrame = 0;
		bool isActiveLife = false;
		bool isFixFrame = false;
		bool isFalling = false;
		bool isDecelerate = false;
		bool isFadeOut = false;
		bool isOnePlay = false;
		bool isInfinity = false;
	};

public:
	explicit Effect(const EffectInfo& info);
private:
	virtual ~Effect() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void SetUseColor(float r = 0.f, float g = 0.f, float b = 0.f, float a = 0.f);
	void SetColor(const XMFLOAT4& color);
	void SetFadeOut(bool isActive, float speed);
	void SetAlpha(float alpha);
	void SetFixFrame(int frame);
	void SetRotation(float degree);

private:
	EffectInfo				_info;
	XMFLOAT4				_color;
	Engine::Animation*		_pAnimation = nullptr;
	Engine::Transform*		_pTarget = nullptr;
	Engine::SpriteRenderer* _pSpriteRenderer = nullptr;

	float					_originSpeed = 0.f;
	float					_elapsed = 0.f;
	float					_alpha = 1.f;
	bool					_isLastFrame = false;
};

