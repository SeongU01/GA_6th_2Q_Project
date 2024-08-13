#include "MPHUD.h"
#include "PlayerMP.h"
#include "Collider.h"
#include "ToolTip.h"
#include "Button.h"
#include "Client_Define.h"
MPHUD::MPHUD(PlayerMP* _Mp, int index)
	:UIComponent(L"MPHUD")
{

	_mpColor = index;
	_pMP = _Mp;
}

void MPHUD::Awake()
{
}

void MPHUD::Start()
{
	UI::UIInfo info;
	info = CreateInfo(L"MPBackground", L"UI_HUD_MP_back", 0, { 50,0 , 0.f }, { 0.7f, 0.7f,1.f }, &transform);
	UI* pui= AddUI(info);
	_ptoolTip = AddComponent<ToolTip>(L"MPTool"); //마나 안내
	_ptoolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"UI_Cost_Mana"), Vector3(0.0f, 0.0f, 0.0f));
	Button* btn = AddComponent<Button>();
	btn->SetRange({ transform.GetPosition().x+50,transform.GetPosition().y,0}, {pui->GetSize().width, pui->GetSize().height});
	Engine::GameObject& obj = GetOwner();
	btn->SetOnHover([&obj] {
		ToolTip* pToolTip = obj.GetComponent<ToolTip>(L"MPTool");
		pToolTip->ActiveToolTip(true);
		});
	btn->SetCancel([&obj] {
		ToolTip* pToolTip = obj.GetComponent<ToolTip>(L"MPTool");
		pToolTip->ActiveToolTip(false);
		});

	for (int i = 0; i < 5; i++) {
		info = CreateInfo(L"MPState", L"UI_HUD_MP", 1, {15+(float)((i * 18)),0 , 2.f }, { 0.7f, 0.7f,1.f }, &transform);
		_MPBar.push_back(AddUI(info));
	}
}

void MPHUD::Update(const float& deltaTime)
{
	int currentHP = _pMP->GetMP();
	for (int i = 0; i < 5; i++)
	{
		if (i < currentHP)
			_MPBar[i]->SetFrame(_mpColor);
		else
			_MPBar[i]->SetFrame(1);
	}
}

void MPHUD::LateUpdate(const float& deltaTime)
{
} 
