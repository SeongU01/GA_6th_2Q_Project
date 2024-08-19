#include "MainGame.h"
#include "TitleScene.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "DataManager.h"
#include "CardManager.h"
#include "EventManager.h"

#include "Card.h"
#include "TestScene.h"
#include "Client_Define.h"

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

	_pGameManager->SetSortGroup((int)RenderGroup::Object, [](Engine::GameObject* src, Engine::GameObject* dst)->bool
		{
			Vector3 srcPosition = src->transform.position;
			Vector3 dstPosition = dst->transform.position;
			return srcPosition.y < dstPosition.y;
		});

	_pGameManager->SetSortGroup((int)RenderGroup::UI, [](Engine::GameObject* src, Engine::GameObject* dst)->bool
		{
			Vector3 srcPosition = src->transform.position;
			Vector3 dstPosition = dst->transform.position;
			return srcPosition.z < dstPosition.z;
		});

	_pGameManager->SetSortGroup((int)RenderGroup::Fade, [](Engine::GameObject* src, Engine::GameObject* dst)->bool
		{
			Vector3 srcPosition = src->transform.position;
			Vector3 dstPosition = dst->transform.position;
			return srcPosition.z < dstPosition.z;
		});

	_pGameManager->SetSortGroup((int)RenderGroup::Card, [](Engine::GameObject* src, Engine::GameObject* dst)->bool
		{
			Vector3 srcPosition = src->transform.position;
			Vector3 dstPosition = dst->transform.position;
			return srcPosition.x + src->GetComponent<Card>()->priority < dstPosition.x + dst->GetComponent<Card>()->priority;
		});	

	Engine::ResourceManager::GetInstance()->LoadTexture(3, (filePath + L"Texture").c_str());
	Engine::ResourceManager::GetInstance()->LoadAnimation(4, (filePath + L"Data/Animation").c_str());
	Engine::SoundManager::GetInstance()->LoadSound(multibyteFilePath);
	

	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::SFX, 0.6f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::BGM, 1.f);
	Engine::SoundManager::GetInstance()->SetMasterVolume(1.f);

	// 공통 데이터
	_pDataManager = DataManager::GetInstance();
	_pDataManager->LoadToolTip((filePath + L"Data/ToolTip").c_str());
	_pDataManager->LoadEnemySpawn((filePath + L"Data/Wave").c_str());
	_pDataManager->LoadMap((filePath + L"Data/Map").c_str());
	_pDataManager->LoadObjectArrange((filePath + L"Data/ObjectArrange").c_str());
	_pDataManager->LoadAttackRangeData((filePath + L"Data/Card").c_str());

	// 카드 데이터
	_pCardManager = CardManager::GetInstance();
	_pCardManager->LoadCard((filePath + L"Data/Card").c_str());
	_pCardManager->SetDontDestroyObject(true);
	_pCardManager->SetRenderGroup((int)RenderGroup::None);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"", _pCardManager);

	// 이벤트 매니저
	EventManager* pEventManager = EventManager::GetInstance();
	pEventManager->SetDontDestroyObject(true);
	pEventManager->SetRenderGroup((int)RenderGroup::None);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"", pEventManager);

	_pGameManager->ChagneScene(TestScene::Create());

	return true;
}

void MainGame::Free()
{
	SafeRelease(_pDataManager);
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
