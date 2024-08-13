#include "TimerHUD.h"
#include "Client_Define.h"

#include "TimerSystem.h"
#include "TextRenderer.h"
#include "ToolTip.h"
#include "Button.h"

TimerHUD::TimerHUD()
	:UIComponent(L"TimerHUD")
{
	_pTimer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<TimerSystem>(); //타이머시스템
}

void TimerHUD::Awake()
{
}

void TimerHUD::Start()
{
	UI::UIInfo info;
	UI* pUI;
	info = CreateInfo(L"Timer_Back", L"UI_HUD_Timer_Back", 0, { 210.0f , 980.f, -1.f }, { 1.0f, 1.0f, 1.0f }, &transform);
	UI* backpUI = AddUI(info);
	info = CreateInfo(L"Timer_Back", L"UI_HUD_Timer_Box", 0, { 210.0f , 1030.f, -1.f }, { 1.0f, 1.3f, 1.0f }, &transform);
	pUI = AddUI(info);
	info = CreateInfo(L"Timer_Red", L"UI_HUD_Timer_Gage", 0, { 147.f , 1030.f, 0.f }, { 0.5f, 1.0f, 0.f }, &transform);
	_pRed = AddUI(info);
	info = CreateInfo(L"Timer_Orange", L"UI_HUD_Timer_Gage", 1, { 273.f, 1030.f, 0.f }, { 0.5f, 1.0f, 0.f }, &transform);
	_pYellow = AddUI(info);
	info = CreateInfo(L"Timer_Back2", L"UI_HUD_Timer_Box", 1, { 210.0f , 1030.f, 0.f }, { 1.f, 1.f, 0.f }, &transform);
	pUI = AddUI(info);
	//텍스트
	Engine::GameObject* pTextobj = Engine::GameObject::Create();
	_pText = pTextobj->AddComponent<Engine::TextRenderer>(L"Timer", D2D1::ColorF::White, 70);
	_pText->SetDrawRect(200.f, 100.f);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pTextobj); pTextobj->SetRenderGroup((int)RenderGroup::UI);
	//아래툴팁
	ToolTip* _ptoolTip = pTextobj->AddComponent<ToolTip>(L"TimerTool1"); //마나 안내
	_ptoolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_001"), Vector3(300.0f, -100.0f, 0.0f));
	Engine::GameObject& oOwner = *pTextobj;
	Button* btn = pTextobj->AddComponent<Button>();
	btn->SetRange(info.position, backpUI->GetSize());
	btn->SetOnHover([&oOwner] {
		ToolTip* pToolTip = oOwner.GetComponent<ToolTip>(L"TimerTool1");
		pToolTip->ActiveToolTip(true);
		});
	btn->SetCancel([&oOwner] {
		ToolTip* pToolTip = oOwner.GetComponent<ToolTip>(L"TimerTool1");
		pToolTip->ActiveToolTip(false);
		});
	//상단 타이머
	info = CreateInfo(L"Timer_top_back", L"UI_HUD_Timer_Top", 0, { 960, 30, 0.f }, { 1.0f, 1.0f, 1.0f }, &transform);
	AddUI(info);
	info = CreateInfo(L"Timer_top_red", L"UI_HUD_Timer_Top", 3, { 960, 30, 0.f }, { 1.0f, 1.0f, 1.0f }, &transform);
	_pTopDefault = AddUI(info);
	//info = CreateInfo(L"Timer_top_Orange", L"UI_HUD_Timer_Top", 4, { 960, 30, 0.f }, { 1.0f, 1.0f, 1.0f }, &transform);
	//_pTopSkill = AddUI(info);
	//위 툴팁
	_ptoolTip = AddComponent<ToolTip>(L"TimerTool2"); //마나 안내
	_ptoolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(L"Object_Structure_001"), Vector3(300.0f, 100.0f, 0.0f));
	Engine::GameObject& pOwner = transform.GetOwner();
	btn = AddComponent<Button>();
	btn->SetRange(info.position, _pTopDefault->GetSize());
	btn->SetOnHover([&pOwner] {
		ToolTip* pToolTip = pOwner.GetComponent<ToolTip>(L"TimerTool2");
		pToolTip->ActiveToolTip(true);
		});
	btn->SetCancel([&pOwner] {
		ToolTip* pToolTip = pOwner.GetComponent<ToolTip>(L"TimerTool2");
		pToolTip->ActiveToolTip(false);
		});
}

void TimerHUD::Update(const float& deltaTime)
{
	float timer = _pTimer->GetRemainingTime();
	if (timer > 30) // 주황 게이지 변경
	{
		float rate = (1 + int((timer - 30.f) / 5.f)) / 6.f;
		int rates = int(6 - ((timer - 30.f) / 5));
		_pYellow->SetOffsetPosition(Vector3(-10.8f * rates, 0.f, 0.f));
		_pYellow->SetScale({ 0.5f * rate, 1.0f, 0.f });
		//  _RemainingUI[1]->SetOffsetPosition(Vector3(-(126* 0.5f *0.5f* (1.f - rate)), 0.f, 0.f)); 흐아아아앙
	}
	else // 빨강 게이지 변경
	{
		_pYellow->SetScale({ 0.f,0.f,0.f });
		float rate = (1 + int(timer / 5.f)) / 6.f;
		int rates = int(6 - (timer / 5));
		_pRed->SetOffsetPosition(Vector3(-10.8f * rates, 0.f, 0.f));
		_pRed->SetScale({ 0.5f * rate, 1.0f, 0.f });
	}
	if (timer <= 0) { 
	    //Time::SetSlowTime(0.0f);   
		_pRed->SetScale({ 0.f,0.f,0.f });
	}
	//글씨조정
	swprintf(_buffer, sizeof(_buffer) / sizeof(_buffer[0]), L"%02d:%02d", (int)timer, (int)(timer * 100) % 100);
	_pText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
	_pText->transform.SetPosition({ 120,920 });
	_pText->SetText(_buffer);	

	//상단 타이머ui
	_pCurrentValue = _pTimer->GetRemainingTime();
	float rate = _pCurrentValue / _maxValue;//60/60 =1 20/60 =0.3...
	_pTopDefault->SetOffsetPosition(Vector3(_pTopDefault->GetImageSize().width * -0.5f * (1.f - rate), 0.f, 0.f));
	_pTopDefault->SetScale({ rate, 1.0f, 0.f }); //1~0
	//사용된 시간(주황탑

}

void TimerHUD::LateUpdate(const float& deltaTime)
{
}
