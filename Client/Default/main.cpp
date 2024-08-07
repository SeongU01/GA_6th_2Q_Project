#include "MainGame.h"

#ifdef _DEBUG
	#ifdef UNICODE
	#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
	#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

void CheckMemoryLeaks()
{
	_CrtDumpMemoryLeaks();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//_CrtSetBreakAlloc(1482);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MainGame* pMainGame = MainGame::Create(hInstance);
	pMainGame->Run();

	SafeRelease(pMainGame);
	atexit(CheckMemoryLeaks);

	return EXIT_SUCCESS;
}