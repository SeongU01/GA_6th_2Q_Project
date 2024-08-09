#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class SpriteRenderer;
}

class Fade : public Engine::MonoBehavior
{
public:
	enum Fade_Option { Fade_In, Fade_Out, Fade_OutIn };
	struct FadeInfo
	{
		Fade_Option		option;
		unsigned int	color;
		float			duration;
		float			alpha;
		float			life;
		float			outInDelay = 0.5f;
		float			delay = 0.f;		
	};

public:
	explicit Fade(const FadeInfo& info);
private:
	virtual ~Fade() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	FadeInfo				_fadeInfo;
	D2D1_RECT_F				_drawRect;
	Engine::SpriteRenderer* _pSpriteRenderer = nullptr;
	float					_elapsed = 0.f;
	bool					_isOutIn = false;
};

