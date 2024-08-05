#include "Canvas.h"
#include "MainUHD.h"
void Canvas::Initialize(const char* name)
{
	if (name == "Main") {
		AddComponent<MainUHD>();
	}
	SetName(name);
	SetRenderGroup(1);//??
}


Canvas* Canvas::Create(const char* name)
{
	Canvas* pInstance = new Canvas;
	pInstance->Initialize(name);

	return pInstance;
}