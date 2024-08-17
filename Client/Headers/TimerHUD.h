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
	UI* _pYellow = nullptr; //�ϴ� Ÿ�̸�
	UI* _pRed = nullptr; //�ϴ� Ÿ�̸�
	UI* _pTopDefault = nullptr; //��� Ÿ�̸�(�⺻Ÿ�̸�
	
	D2D1_SIZE_F	_imageSize{};

	UI* _pTopSkill = nullptr; //��� Ÿ�̸�(��ųŸ�̸�
	UI* _pBene = nullptr; //Ÿ�������� �����
	Engine::TextRenderer* _pText = nullptr;
	wchar_t _buffer[32]{};
};

