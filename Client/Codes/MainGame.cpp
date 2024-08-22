#include "MainGame.h"
#include "TitleScene.h"
#include "Loading.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "DataManager.h"
#include "EventManager.h"

#include "Card.h"
#include "TestScene.h"
#include "Client_Define.h"

MainGame::MainGame()
	: _pGameManager(Engine::GameManager::GetInstance()), _pDataManager(DataManager::GetInstance())
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

	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::Card, 0.7f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::BGM, 0.8f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::AddSFX, 0.6f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::Battle, 0.4f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::Player, 0.7f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::SFX, 0.7f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::Voice, 1.f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::FirstEnemy, 1.0f);
	Engine::SoundManager::GetInstance()->SetVolume((int)SoundGroup::Operator, 1.0f);
	Engine::SoundManager::GetInstance()->SetMasterVolume(1.f);


	std::wstring filePath = rootPath;

	DataManager* pDataManager = DataManager::GetInstance();
	pDataManager->LoadToolTip((filePath + L"Data/ToolTip").c_str());
	pDataManager->LoadCutScene((filePath + L"Data/CutScene").c_str());
	pDataManager->LoadEnemySpawn((filePath + L"Data/Wave").c_str());
	pDataManager->LoadMap((filePath + L"Data/Map").c_str());
	pDataManager->LoadObjectArrange((filePath + L"Data/ObjectArrange").c_str());
	pDataManager->LoadAttackRangeData((filePath + L"Data/Card").c_str());

	Engine::ResourceManager::GetInstance()->LoadTexture(3, (filePath + L"Loading").c_str());
	
	_pGameManager->ChangeScene(Loading::Create());

	return true;
}

void MainGame::Free()
{
	SafeRelease(_pDataManager);
	// SafeRelease(_pGameManager);
}

MainGame* MainGame::Create(HINSTANCE hInstance)
{
	MainGame* pInstance = new MainGame;

	if (pInstance->Initialize(hInstance))
		return pInstance;

	SafeRelease(pInstance);
	return nullptr;
}
