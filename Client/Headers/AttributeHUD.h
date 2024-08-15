#pragma once
#include "UIComponent.h"

class Attribute;
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
	Attribute* _pAttribute = nullptr;
};

