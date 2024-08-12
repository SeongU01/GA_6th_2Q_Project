#include "TimerHUD.h"

#include "TextRenderer.h"
#include "TimerSystem.h"

#include "Client_Define.h"

TimerHUD::TimerHUD()
	:UIComponent(L"HP")
{
}

void TimerHUD::Awake()
{
}

void TimerHUD::Start()
{
	UI::UIInfo info;
	UI* pUI;
	info = CreateInfo(L"Timer_Back", L"UI_HUD_Timer_Box", 0, { 210.0f , 1000.f, -1.f }, { 1.0f, 1.3f, 1.0f }, &transform);
	pUI = AddUI(info);
	info = CreateInfo(L"Timer_Red", L"UI_HUD_Timer_Gage", 0, { 147.f , 1000.f, 0.f }, { 0.5f, 1.0f, 0.f }, &transform);
	_pRed = AddUI(info);
	info = CreateInfo(L"Timer_Orange", L"UI_HUD_Timer_Gage", 1, { 273.f, 1000.f, 0.f }, { 0.5f, 1.0f, 0.f }, &transform);
	_pYellow = AddUI(info);
	info = CreateInfo(L"Timer_Back2", L"UI_HUD_Timer_Box", 1, { 210.0f , 1000.f, 0.f }, { 1.f, 1.f, 0.f }, &transform);
	pUI = AddUI(info);

	info = CreateInfo(L"Timer_Orange", L"UI_HUD_Timer_Gage", 1, { 960, 10, 0.f }, { 7.0f, 1.0f, 0.f }, &transform);
	_pTopDefault = AddUI(info);
	info = CreateInfo(L"Timer_Orange", L"UI_HUD_Timer_Gage", 1, { 960, 10, 0.f }, { 0.5f, 1.0f, 0.f }, &transform);
	_pTopSkill = AddUI(info);

	Engine::GameObject* pObj = Engine::GameObject::Create();
	_pText = pObj->AddComponent<Engine::TextRenderer>(L"Timer", D2D1::ColorF::Red);
	_pText->SetDrawRect(200.f, 100.f);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pObj); pObj->SetRenderGroup((int)RenderGroup::UI);	
	_pTimer = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<TimerSystem>(); //타이머시스템

	_pCurrentValue = _pTimer->GetRemainingTime();
	_maxValue = 10.0f;
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
	swprintf(_buffer, sizeof(_buffer) / sizeof(_buffer[0]), L"Timer : %02d:%02d", (int)timer, (int)(timer * 100) % 100);
	_pText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
	_pText->transform.SetPosition({ 130,910 });
	_pText->SetText(_buffer);	

	//상단 타이머ui
	_pCurrentValue = _pTimer->GetRemainingTime();
	float rate = _pCurrentValue / _maxValue;

	_pTopDefault->SetOffsetPosition(Vector3(-_imageSize.width * 0.5f * (1.f - rate), 0.f, 0.f));
	_pTopDefault->SetScale({ rate, 1.0f, 0.f });
}

void TimerHUD::LateUpdate(const float& deltaTime)
{
}
