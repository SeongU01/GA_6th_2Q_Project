#pragma once
#include "UIComponent.h"

namespace Engine{
	class TextRenderer;
}

class TimerSystem;
class TimerHUD : public UIComponent
{
public:
	explicit TimerHUD();
private:
	virtual ~TimerHUD() = default;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
private:
	TimerSystem* pTimer = nullptr;
	UI* pYellow = nullptr;
	UI* pRed = nullptr;
	Engine::TextRenderer* pText = nullptr;
	wchar_t _buffer[32];
};

