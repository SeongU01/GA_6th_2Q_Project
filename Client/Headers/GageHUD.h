#pragma once
#include "UIComponent.h"

class GageHUD : public UIComponent
{
public:
	explicit GageHUD(const Vector3& position, float* pCurrentValue, float maxValue,int num);
private:
	virtual ~GageHUD() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	Vector3		_position;
	D2D1_SIZE_F	_imageSize{};
	UI*			_pGage = nullptr;
	float*		_pCurrentValue = nullptr;
	float		_maxValue = 0.f;
	int			_number; // 0==����, 1==������
};

