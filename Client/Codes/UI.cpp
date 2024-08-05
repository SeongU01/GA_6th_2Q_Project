#include "UI.h"

// Component
#include "Client_Define.h"

const D2D1_SIZE_F& UI::GetImageSize()
{
    //이미지 사이즈를 가져오기
    return _imageSize;
}

void UI::SetPosition(const Vector3& position)
{
    //위치 조정
    _info.position = position;
}


void UI::SetScale(const Vector3& scale)
{
    //스케일 조정
    _info.scale = scale;
}

void UI::SetScaleRate(float rate)
{
    //반전값 조정
    _info.scale.x = _pTransform->GetScale().x * rate;
    _scaleRate = rate;
}

void UI::SetRotation(float angle)
{
    //회전 조정
    _rotation = angle;
}


void UI::AddRotation(float angle)
{
    //회전율추가
    _rotation += angle;

    if (_rotation >= 360.f)
        _rotation = 0.f;
}

void UI::AddScale(const Vector3& scale)
{
    //크기추가
    _info.scale += scale;
}


void UI::Initialize(UIInfo& info)
{
    _info = info;
    SetName(_info.name);

    _pTransform->SetParent(_info.pParent);
    _pTransform->SetPosition(_info.position);
    _pTransform->SetScale(_info.scale);
    SetRenderGroup((int)RenderGroup::UI);
    _pSpriteRenderer->BindTexture(Resource::FindTexture(info.textureTag));
    _pSpriteRenderer->NotAffectCamera();
}

void UI::Free()
{
}

UI* UI::Create(UIInfo& info)
{
    UI* pInstance = new UI;
    pInstance->Initialize(info);

    return pInstance;
}
