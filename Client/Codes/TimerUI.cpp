#include "TimerUI.h"
#include "TimerSystem.h"
#include "TextRenderer.h"


#include "Client_Define.h"

void TimerUI::Initialize()
{
	Engine::TextRenderer* text = AddComponent<Engine::TextRenderer>("Timer", D2D1::ColorF::Red);
	text->SetDrawRect(D2D1::RectF(0, 0, 1000, 1000));

	TimerSystem* Timer = AddComponent<TimerSystem>();
	Timer->SetTextComponent(text);
	SetRenderGroup((int)RenderGroup::UI);
}

TimerUI* TimerUI::Create()
{
	TimerUI* pInstance = new TimerUI();
	pInstance->Initialize();
	return pInstance;
}
