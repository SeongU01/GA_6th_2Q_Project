#include "Canvas.h"
#include "MainHUD.h"
void Canvas::Initialize(const char* name)
{
	if (name == "Main") {
		AddComponent<MainHUD>();
	}
	SetName(name);
	SetRenderGroup(0);//??

}


Canvas* Canvas::Create(const char* name)
{
	Canvas* pInstance = new Canvas;
	pInstance->Initialize(name);

	return pInstance;
}