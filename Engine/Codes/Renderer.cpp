#include "Renderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "GameManager.h"

using namespace Engine;

void Engine::Renderer::Render_GameObject()
{
    if (!_isSetUp)
        return;
 
    _info.pDeviceContext->BeginDraw();
    _info.pDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::Gray));

    D2D1_MATRIX_3X2_F cameraMatrix = _pCurrCamera->GetCameraMatrix();
    D2D1InvertMatrix(&cameraMatrix);

    for (int i = 0; i < _info.size; i++)
    {
        if (nullptr != _sortInfo[i])
            _renderGroup[i].sort(_sortInfo[i]);

        for (auto& Object : _renderGroup[i])
        {
            memcpy(&Object->_cameraMatrix, &cameraMatrix, sizeof(D2D1_MATRIX_3X2_F));
            Object->Render();
        }

        _renderGroup[i].clear();
    }

    _info.pDeviceContext->EndDraw();
}

bool Engine::Renderer::SetUpRenderer(const RenderGroupInfo& info)
{
    if (_isSetUp)
        return false;

    _info = info;
    _renderGroup.resize(_info.size);
    _sortInfo.resize(_info.size);
    _isSetUp = true;

    _pCurrCamera = GameManager::GetInstance()->GetCurrCamera();

    return true;
}

void Engine::Renderer::SetSortGroup(int sortGroup, bool(*sortFunc)(GameObject*, GameObject*))
{
    _sortInfo[sortGroup] = sortFunc;
}

bool Engine::Renderer::AddRenderGroup(int group, GameObject* pObject)
{    
    if (nullptr == pObject || pObject->IsDead())
        return false;

    _renderGroup[group].push_back(pObject);

    return true;
}

void Engine::Renderer::ResetRenderGroup()
{
    for (int i = 0; i < _info.size; i++)
        _renderGroup[i].clear();
}

void Engine::Renderer::Free()
{
    for (auto& Group : _renderGroup)
        Group.clear();

    _renderGroup.clear();
    _renderGroup.shrink_to_fit();
}

Renderer* Engine::Renderer::Create()
{
    return new Renderer;
}
