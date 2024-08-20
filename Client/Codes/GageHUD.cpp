#include "GageHUD.h"
#include "Client_Define.h"

#include "ToolTip.h"
#include "Button.h"
#include "UI.h"

GageHUD::GageHUD(const Vector3& position, float* pCurrentValue, float maxValue, int num)
	: UIComponent(L"GageHUD"), _position(position), _pCurrentValue(pCurrentValue), _maxValue(maxValue),_number(num)
{
}

void GageHUD::Awake()
{
	UI* uis = AddUI(CreateInfo(L"Gage_BackGround", L"UI_HUD_MP_recharge", 0, _position, Vector3(1.f, 1.f, 1.f), &transform));
	_pGage = AddUI(CreateInfo(L"Gage", L"UI_HUD_MP_recharge", 1, _position, Vector3(1.f, 1.f, 1.f), &transform));

	Engine::Texture* pTexture = Resource::FindTexture(L"UI_Gage");
	_imageSize = pTexture->GetImage(0)->GetSize(); 

	ToolTip* _ptoolTip = AddComponent<ToolTip>(L"reChargeTool"); //마나 안내
	_ptoolTip->DontDestoryToolTips();
	if(_number==1)
		_ptoolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"UI_Card_Reload_Recovery"), Vector3(1500.0f, 830.0f, 0.0f));
	else
		_ptoolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"UI_Cost_Mana_Recovery"), Vector3(350.0f, 830.0f, 0.0f));
	Engine::GameObject& pObj = GetOwner();
	Button* btn = AddComponent<Button>();
	btn->SetRange(_position, _imageSize);
	btn->SetOnHover([&pObj] {
		ToolTip* pToolTip = pObj.GetComponent<ToolTip>(L"reChargeTool");
		pToolTip->ActiveToolTip(true);
		});
	btn->SetCancel([&pObj] { 
		ToolTip* pToolTip = pObj.GetComponent<ToolTip>(L"reChargeTool");
		pToolTip->ActiveToolTip(false);
		});
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
	
	_pGage->SetOffsetPosition(
		Vector3(-_imageSize.width * 0.5f * (1.f - rate) + (1 - rate) * 12, 0.f, 0.f)
	);
	_pGage->SetScale({ rate, 1.0f, 0.f });
}
