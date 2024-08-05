#include "UI.h"

// Component
#include "Animation.h"

#include "Client_Define.h"

const D2D1_SIZE_F& UI::GetImageSize()
{
    //�̹��� ����� ��������
    _imageSize = _pAnimation->GetImage(_pAnimation->GetCurrFrame())->GetSize();
    return _imageSize;
}

void UI::SetPosition(const Vector3& position)
{
    //��ġ ����
    _info.position = position;
}

void UI::SetOffsetPosition(const Vector3& position)
{
    //������ ����
    _offsetPosition = position;
}

void UI::SetScale(const Vector3& scale)
{
    //������ ����
    _info.scale = scale;
}

void UI::SetScaleRate(float rate)
{
    //������ ����
    _info.scale.x = _originScale.x * rate;
    _scaleRate = rate;
}

void UI::SetRotation(float angle)
{
    //ȸ�� ����
    _rotation = angle;
}

void UI::SetFixFrame(bool isActive, int fixFrame)
{
    //??
    _info.isFixFrame = isActive;
    _info.fixFrame = fixFrame;
}

void UI::AddRotation(float angle)
{
    //ȸ�����߰�
    _rotation += angle;

    if (_rotation >= 360.f)
        _rotation = 0.f;
}

void UI::AddScale(const Vector3& scale)
{
    //ũ���߰�
    _info.scale += scale;
}


void UI::Initialize(UIInfo& info)
{
    _info = info;
    SetName(_info.name);

    _pTransform->SetParent(_info.pParent);
    _pTransform->SetPosition(_info.position);
    _originScale = _info.scale;
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
