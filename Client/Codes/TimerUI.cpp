#include "TimerUI.h"


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

}

TimerUI* TimerUI::Create()
{
	TimerUI* pInstance = new TimerUI();
	pInstance->Initialize();
	return pInstance;
}
