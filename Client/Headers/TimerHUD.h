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
	TimerSystem* _pTimer = nullptr;
	UI* _pYellow = nullptr; //하단 타이머
	UI* _pRed = nullptr; //하단 타이머
	UI* _pTopDefault = nullptr; //상단 타이머(기본타이머
	
	//테스트중, , ,
	D2D1_SIZE_F	_imageSize{};
	float _pCurrentValue = 0.f;
	float		_maxValue = 60.f;

	UI* _pTopSkill = nullptr; //상단 타이머(스킬타이머
	Engine::TextRenderer* _pText = nullptr;
	wchar_t _buffer[32];
};

