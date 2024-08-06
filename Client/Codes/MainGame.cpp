#include "MainGame.h"
#include "TestScene.h"

#include "TimeManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "Client_Define.h"

std::random_device g_rd;
std::mt19937 g_gen(g_rd());

MainGame::MainGame()
	: _pGameManager(Engine::GameManager::GetInstance())
{
}

void MainGame::Run()
{
	_pGameManager->Run();
}

bool MainGame::Initialize(HINSTANCE hInstance)
{
	Engine::GameManager::GameDefaultSetting info;

	info.hInstance = hInstance;
	info.appName = L"Archtype:0";
	info.width = WINCX;
	info.height = WINCY;
	info.layerSize = (int)LayerGroup::End;
	info.renderGroupSize = (int)RenderGroup::End;
	info.maxSoundGroup = (int)SoundGroup::End;
	info.fiexedCount = 50;
	info.isFullScreen = false;

	std::wstring filePath = rootPath;
	std::wstring widebyte = filePath + L"Sound";
	char multibyteFilePath[256];
	const wchar_t* widebyteFilePath = widebyte.c_str();
	wcsrtombs_s(nullptr, multibyteFilePath, &widebyteFilePath, lstrlen(widebyteFilePath), nullptr);
	_pGameManager->Initialize(info);

	_pGameManager->SetSortGroup((int)RenderGroup::UI, [](Engine::GameObject* src, Engine::GameObject* dst)->bool
		{
			Vector3 srcPosition = src->GetTransform()->GetPosition();
			Vector3 dstPosition = dst->GetTransform()->GetPosition();
			return srcPosition.z < dstPosition.z;
		});

	Engine::ResourceManager::GetInstance()->LoadTexture(3, (filePath + L"Texture").c_str());
	Engine::ResourceManager::GetInstance()->LoadAnimation(4, (filePath + L"Data/Animation").c_str());
	//Engine::SoundManager::GetInstance()->LoadSound(multibyteFilePath);
	_pGameManager->ChagneScene(TestScene::Create());


	return true;
}

void MainGame::Free()
{
	SafeRelease(_pGameManager);
}

MainGame* MainGame::Create(HINSTANCE hInstance)
{
	MainGame* pInstance = new MainGame;

	if (pInstance->Initialize(hInstance))
		return pInstance;

	SafeRelease(pInstance);
	return nullptr;
}
