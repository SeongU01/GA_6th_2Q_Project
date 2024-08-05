#include "Canvas.h"
#include "MainHUD.h"
void Canvas::Initialize(const wchar_t* name)
{
	if (name == L"Main") {
		AddComponent<MainHUD>();
	}
	SetName(name);
	SetRenderGroup(0);//??

}


Canvas* Canvas::Create(const wchar_t* name)
{
	Canvas* pInstance = new Canvas;
	pInstance->Initialize(name);

	return pInstance;
}