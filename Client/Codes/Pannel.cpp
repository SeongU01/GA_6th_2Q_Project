#include "Pannel.h"
#include "Client_Define.h"

bool Pannel::Initialize(const PannelInfo& info)
{
    _info = info;

    SetRenderGroup((int)RenderGroup::UI);
    transform.SetParent(_info.parent);
    transform.position = _info.position;

    _pSpriteRenderer->SetOneSelfDraw(true, [&]()
        {            
            D2D1_RECT_F rect{ -_info.size.x * 0.5f, -_info.size.y * 0.5f, _info.size.x * 0.5f, _info.size.y * 0.5f };
            _pSpriteRenderer->DrawFillRect(rect, _info.fillColor, _info.opacity);
            _pSpriteRenderer->DrawRect(rect, _info.outlineColor, _info.lineWidth);
        });

    return true;
}

Pannel* Pannel::Create(const PannelInfo& info)
{
    Pannel* pInstance = new Pannel;

    if (pInstance->Initialize(info))
        return pInstance;

    return pInstance;
}
