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
	ui = CreateInfo(L"Timer", L"UI_HUD_Timer_Box", 0, { 210.0f , 870.f, -1.f }, { 0.4f, 1.0f, 1.0f }, GetTransform());
	_UIs.push_back(UI::Create(ui));
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"Timer", _UIs.back());
	for (int i = 0; i < 12; i++) //빨강
	{
		int num = 0;
		if (i > 8) num = 2;
		else if (i > 5) num = 1;
		ui = CreateInfo(L"Timer", L"UI_HUD_Timer_Gage", num, { 100.f+(20.0f*i), 900.f, 0.f}, {0.1f, 0.1f, 0.f}, GetTransform());
		_UIs.push_back(UI::Create(ui));
		Engine::AddObjectInLayer((int)LayerGroup::UI, L"Timer", _UIs.back());
	}
	//뎁스정렬
	Engine::TextRenderer* text = AddComponent<Engine::TextRenderer>(L"Timer", D2D1::ColorF::Red);
	text->SetDrawRect(D2D1::RectF(100, 800, 300, 900));
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
