#include "TimerUI.h"
#include "TimerSystem.h"
#include "TextRenderer.h"

#include "Client_Define.h"

//ui추가함수 
UI::UIInfo CreateInfo(const wchar_t* name, const wchar_t* tag, int fixframe, Vector3 position, Vector3 scale, Engine::Transform* parent) 
{
	UI::UIInfo info;
	info.name = name;
	info.textureTag = tag;
	info.fixFrame = fixframe;
	info.position = position;
	info.scale = scale;
	info.pParent = parent;
	return info;
}

void TimerUI::Initialize()
{
	//박스
	ui = CreateInfo(L"Timer", L"UI_HUD_Timer_Box", 0, { 210.0f , 900.f, -1.f }, { 1.0f, 1.3f, 1.0f }, GetTransform());
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Timer", UI::Create(ui));

	//for (int i = 0; i < 12; i++) //빨강
	//{
	//	int num = 0;
	//	if (i > 5) num = 1;
	//	ui = CreateInfo(L"Timer", L"UI_HUD_Timer_Gage", num, { 92.f + (21.2f * i), 900.f, 0.f }, { 0.07f, 0.8f, 0.f }, GetTransform());
	//	_UIs.push_back(UI::Create(ui));
	//	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Timer", _UIs.back());
	//}

	ui = CreateInfo(L"Timer", L"UI_HUD_Timer_Gage", 0, { 147.f , 900.f, 0.f }, { 0.5f, 1.0f, 0.f }, GetTransform());
	_UIs.push_back(UI::Create(ui));
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Timer", _UIs.back());

	ui = CreateInfo(L"Timer", L"UI_HUD_Timer_Gage", 1, { 273.f, 900.f, 0.f }, { 0.5f, 1.0f, 0.f }, GetTransform());
	_UIs.push_back(UI::Create(ui));
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Timer", _UIs.back());
	//----------------------
	ui = CreateInfo(L"Timer", L"UI_HUD_Timer_Box", 1, { 210.0f , 900.f, 0.f }, { 1.f, 1.f, 0.f }, GetTransform());
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Timer", UI::Create(ui));

	//뎁스정렬
	Engine::TextRenderer* text = AddComponent<Engine::TextRenderer>(L"Timer", D2D1::ColorF::Red);
	text->SetDrawRect(D2D1::RectF(100, 800, 300, 900));
	text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	TimerSystem* Timer = AddComponent<TimerSystem>();

	Timer->SetTextComponent(text);
	Timer->SetHeartsUIs(_UIs);
	SetRenderGroup((int)RenderGroup::UI);
}

TimerUI* TimerUI::Create()
{
	TimerUI* pInstance = new TimerUI();
	pInstance->Initialize();
	return pInstance;
}
