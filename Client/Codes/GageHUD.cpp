#include "GageHUD.h"
#include "Client_Define.h"

GageHUD::GageHUD(const Vector3& position, float* pCurrentValue, float maxValue)
	: UIComponent(L"GageHUD"), _position(position), _pCurrentValue(pCurrentValue), _maxValue(maxValue)
{
}

void GageHUD::Awake()
{
	AddUI(CreateInfo(L"Gage_BackGround", L"UI_Gage", 0, _position, Vector3(1.f, 1.f, 0.f), &transform));
	_pGage = AddUI(CreateInfo(L"Gage", L"UI_Gage", 1, _position, Vector3(1.f, 1.f, 0.f), &transform));

	Engine::Texture* pTexture = Resource::FindTexture(L"UI_Gage");
	_imageSize = pTexture->GetImage(0)->GetSize();
}

void GageHUD::Start()
{
}

void GageHUD::Update(const float& deltaTime)
{
}

void GageHUD::LateUpdate(const float& deltaTime)
{
	float rate = *_pCurrentValue / _maxValue;
	
	_pGage->SetOffsetPosition(Vector3(-_imageSize.width * 0.5f * (1.f - rate), 0.f, 0.f));
	_pGage->SetScale({ rate, 1.0f, 0.f });
}
