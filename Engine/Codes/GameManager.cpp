#include "GameManager.h"
#include "WinApp.h"
#include "GameObject.h"
#include "Scene.h"
#include "Layer.h"
#include "Renderer.h"
#include "Camera.h"

// Manager
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "GraphicManager.h"
#include "SceneManager.h"

using namespace Engine;

Engine::GameManager::GameManager()
{
    _pInputMgr = InputManager::GetInstance();
    _pTimeMgr = TimeManager::GetInstance();
    _pResourceMgr = ResourceManager::GetInstance();
    _pSoundMgr = SoundManager::GetInstance();
    _pGraphicMgr = GraphicManager::GetInstance();
    _pSceneMgr = SceneManager::Create();
    _pRenderer = Renderer::Create();
    _pCamera = Camera::Create();   
}

void Engine::GameManager::Run()
{
    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;
            else
            {
                DispatchMessage(&msg);
            }
        }
        else
        {
            StartGame();
            FixedUpdateGame(_fixedCount);

            if (GameState::Game_End == UpdateGame())
                break;

            if (GameState::Game_End == LateUpdateGame())
                break;

            RenderGame();
        }
    }
}

void Engine::GameManager::StartGame()
{
    _pSceneMgr->Start();
}

void Engine::GameManager::FixedUpdateGame(int count)
{
    _elapsed += _pTimeMgr->GetDeltaTime();

    float fixed = 1.f / count;
    
    if (_elapsed >= fixed)
    {
        _pSceneMgr->FixedUpdate();
        _pCamera->FixedUpdate();
        _elapsed -= fixed;
    }
}

int Engine::GameManager::UpdateGame()
{
    int isEvent = 0;

    _pTimeMgr->Update();
    float deltaTime = _pTimeMgr->GetDeltaTime();
    _pInputMgr->Update(deltaTime);
    isEvent = _pSceneMgr->Update(deltaTime);
    _pCamera->Update(deltaTime);

    return isEvent;
}

int Engine::GameManager::LateUpdateGame()
{
    int isEvent = 0;    
    float deltaTime = _pTimeMgr->GetDeltaTime();
    
    isEvent = _pSceneMgr->LateUpdate(deltaTime);
    _pSceneMgr->AddRenderGroup();
    _pCamera->LateUpdate(deltaTime);
    _pSoundMgr->Update(deltaTime);

    return isEvent;
}

void Engine::GameManager::RenderGame()
{        
    _pRenderer->Render_GameObject();
}

bool Engine::GameManager::Initialize(const GameDefaultSetting& info)
{
    _pWinApp = WinApp::Create(info.hInstance, info.appName, info.width, info.height, info.isFullScreen);

    if (nullptr == _pWinApp)
        return false;
   
    if (false == _pGraphicMgr->SetUpGraphic(_pWinApp->GetWindow()))
        return false;

    if (false == _pInputMgr->SetUpInputDevice(info.hInstance, _pWinApp->GetWindow()))
        return false;

    if (false == _pSoundMgr->SetUpSound(info.maxSoundGroup))
        return false;

    Renderer::RenderGroupInfo renderInfo{};

    renderInfo.pDeviceContext = _pGraphicMgr->GetDeviceContext();
    renderInfo.size = info.renderGroupSize;
    renderInfo.width = info.width;
    renderInfo.height = info.height;

    if (false == _pRenderer->SetUpRenderer(renderInfo))
        return false;

    if (false == _pSceneMgr->SetUpLayer(info.layerSize))
        return false;

    _pResourceMgr->SetWICFactory(_pGraphicMgr->GetWICFactory());

    _fixedCount = info.fiexedCount;

    return true;
}

HWND Engine::GameManager::GetWindow() const
{
    return _pWinApp->GetWindow();
}

void Engine::GameManager::SetSlowTime(float rate)
{
    _pTimeMgr->SetSlowTime(rate);
}

bool Engine::GameManager::ChangeScene(Scene* pScene)
{
    return _pSceneMgr->ChangeScene(pScene);
}

std::list<GameObject*>* Engine::GameManager::FindObjectList(int layerGroup, const wchar_t* listTag)
{
    return _pSceneMgr->FindObjectList(layerGroup, listTag);
}

GameObject* Engine::GameManager::FindObject(int layerGroup, const wchar_t* listTag, const wchar_t* objectTag)
{
    return _pSceneMgr->FindObject(layerGroup, listTag, objectTag);
}

void Engine::GameManager::Free()
{
    SafeRelease(_pWinApp);
    SafeRelease(_pCamera);
    SafeRelease(_pRenderer);
    SafeRelease(_pSceneMgr);
    SafeRelease(_pInputMgr);
    SafeRelease(_pTimeMgr);
    SafeRelease(_pResourceMgr);
    SafeRelease(_pSoundMgr);
    SafeRelease(_pGraphicMgr);
}

bool Engine::GameManager::AddRenderGroup(int renderGroup, GameObject* pObject)
{
    return _pRenderer->AddRenderGroup(renderGroup, pObject);
}

void Engine::GameManager::SetSortGroup(int sortGroup, bool(*sortFunc)(GameObject*, GameObject*))
{
    _pRenderer->SetSortGroup(sortGroup, sortFunc);
}

size_t Engine::GameManager::GetUsedVRAM()
{
    return _pGraphicMgr->GetUsedVRAM();
}

void Engine::GameManager::CameraShake(float shakeTime, float shakePower)
{
    _pCamera->CameraShake(shakeTime, shakePower);
}

void Engine::GameManager::SetCameraTarget(Transform* pTransform)
{
    _pCamera->SetTarget(pTransform);
}

void Engine::GameManager::SetCameraOffset(const Vector3& offset)
{
    _pCamera->SetOffset(offset);
}

void Engine::GameManager::SetCameraMaxPosition(const Vector3& position)
{
    _pCamera->SetMaxPosition(position);
}

void Engine::GameManager::SetCameraMinPosition(const Vector3& position)
{
    _pCamera->SetMinPosition(position);
}

void Engine::GameManager::SetCameraArea(const Vector3& area)
{
    _pCamera->SetArea(area);
}

Camera* Engine::GameManager::GetCurrCamera()
{
    return _pCamera;
}

void Engine::GameManager::RestoreDisplay()
{
    _pWinApp->RestoreDisplay();
}

void Engine::GameManager::LoadSound(const char* filePath)
{
    _pSoundMgr->LoadSound(filePath);
}

void Engine::GameManager::ClearObjectList(int layerGroup, const wchar_t* listTag)
{
    _pSceneMgr->ClearObjectList(layerGroup, listTag);
    _pRenderer->ResetRenderGroup();
}

void Engine::GameManager::ClearLayer(int layerGroup)
{
    _pSceneMgr->ClearLayer(layerGroup);
    _pRenderer->ResetRenderGroup();
}

bool Engine::GameManager::AddObjectInLayer(int layerGroup, const wchar_t* listTag, GameObject* pObject)
{
    return _pSceneMgr->AddObjectInLayer(layerGroup, listTag, pObject);
}

void Engine::GameManager::RemoveAll()
{
    _pSceneMgr->RemoveAll();
}
