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
	info = CreateInfo(L"Timer_Back", L"UI_HUD_Timer_Box", 0, { 210.0f , 900.f, -1.f }, { 1.0f, 1.3f, 1.0f }, &transform);
	pUI = AddUI(info);
	info = CreateInfo(L"Timer_Red", L"UI_HUD_Timer_Gage", 0, { 147.f , 900.f, 0.f }, { 0.5f, 1.0f, 0.f }, &transform);
	pRed = AddUI(info);
	info = CreateInfo(L"Timer_Orange", L"UI_HUD_Timer_Gage", 1, { 273.f, 900.f, 0.f }, { 0.5f, 1.0f, 0.f }, &transform);
	pYellow = AddUI(info);
	info = CreateInfo(L"Timer_Back2", L"UI_HUD_Timer_Box", 1, { 210.0f , 900.f, 0.f }, { 1.f, 1.f, 0.f }, &transform);
	pUI = AddUI(info);

	Engine::GameObject* pObj = Engine::GameObject::Create();
	pText = pObj->AddComponent<Engine::TextRenderer>(L"Timer", D2D1::ColorF::Red);
	pText->SetDrawRect(D2D1::RectF(100, 800, 300, 900));
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"SelectUI", pObj); pObj->SetRenderGroup((int)RenderGroup::UI);
	pTimer = Engine::FindObject((int)LayerGroup::UI, L"TimerSystem", NULL)->GetComponent<TimerSystem>(); //타이머시스템

	SetDontDestroyObject(true);
}

void TimerHUD::Update(const float& deltaTime)
{
	float timer = pTimer->GetRemainingTime();
	if (timer > 30) // 주황 게이지 변경
	{
		float rate = (1 + int((timer - 30.f) / 5.f)) / 6.f;
		int rates = 6 - ((timer - 30.f) / 5);
		pYellow->SetOffsetPosition(Vector3(-10.8 * rates, 0.f, 0.f));
		pYellow->SetScale({ 0.5f * rate, 1.0f, 0.f });
		//  _RemainingUI[1]->SetOffsetPosition(Vector3(-(126* 0.5f *0.5f* (1.f - rate)), 0.f, 0.f)); 흐아아아앙
	}
	else // 빨강 게이지 변경
	{
		pYellow->SetScale({ 0.f,0.f,0.f });
		float rate = (1 + int(timer / 5.f)) / 6.f;
		int rates = 6 - (timer / 5);
		pRed->SetOffsetPosition(Vector3(-10.8 * rates, 0.f, 0.f));
		pRed->SetScale({ 0.5f * rate, 1.0f, 0.f });
	}
	if (timer <= 0) { 
	    Time::SetSlowTime(0.0f);   
	 pRed->SetScale({ 0.f,0.f,0.f });
	}
	swprintf(_buffer, sizeof(_buffer) / sizeof(_buffer[0]), L"Timer : %02d:%02d", (int)timer, (int)(timer * 100) % 100);
	pText->SetText(_buffer);
	

}

void TimerHUD::LateUpdate(const float& deltaTime)
{
}
