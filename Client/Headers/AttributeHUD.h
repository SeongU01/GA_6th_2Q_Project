#pragma once
#include "UIComponent.h"

class Attribute;
class ToolTip;
class AttributeHUD : public UIComponent
{
public:
	explicit AttributeHUD(Attribute* pAttribute);
private:
	virtual ~AttributeHUD() = default;

public:
	// UIComponent��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	ToolTip* _pToolTip = nullptr;
	Attribute* _pAttribute = nullptr;
	int _currDirectionX = 1;
};