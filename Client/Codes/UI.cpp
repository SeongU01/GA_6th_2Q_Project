#include "UI.h"

// Component
#include "Client_Define.h"

const D2D1_SIZE_F& UI::GetImageSize()
{
    //�̹��� ����� ��������
    _imageSize = Resource::FindTexture(_info.textureTag)->GetImage(_info.fixFrame)->GetSize();
    return _imageSize;
}

const D2D1_SIZE_F& UI::GetSize()
{
    _imageSize = Resource::FindTexture(_info.textureTag)->GetImage(_info.fixFrame)->GetSize();
    _realSize = { _imageSize.width * _info.scale.x, _imageSize.height * _info.scale.y };
    return _realSize;
}

void UI::SetFrame(int index)
{
    _info.fixFrame = index;
    _pSpriteRenderer->SetIndex(_info.fixFrame);
}

void UI::SetPosition(const Vector3& position)
{
    //��ġ ����
    _info.position = position;
    _pTransform->SetPosition(_info.position + _offsetPosition);
}

void UI::SetOffsetPosition(const Vector3& position)
{
    _offsetPosition = position;
    _pTransform->SetPosition(_info.position + _offsetPosition);
}

void UI::SetScale(const Vector3& scale)
{
    //������ ����
    _info.scale = scale;
    _pTransform->SetScale(_info.scale);
}

void UI::SetScaleRate(float rate)
{
    //������ ����
    _info.scale.x = _pTransform->GetScale().x * rate;
    _scaleRate = rate;
    _pTransform->SetScale(_info.scale);
}

void UI::SetRotation(float angle)
{
    //ȸ�� ����
    _rotation = angle;
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
    _pTransform->SetScale(_info.scale);
}


void UI::Initialize(const UIInfo& info)
{
    _info = info;
    SetName(_info.name);
    SetRenderGroup((int)RenderGroup::UI);
    SetNotAffectCamera(true);

    _pTransform->SetParent(_info.pParent);
    _pTransform->SetPosition(_info.position + _offsetPosition);
    _pTransform->SetScale(_info.scale);

    _pSpriteRenderer->BindTexture(Resource::FindTexture(info.textureTag));
    _pSpriteRenderer->SetIndex(_info.fixFrame);
    _originScale = _info.scale;
}

void UI::Free()
{
}

UI* UI::Create(const UIInfo& info)
{
    UI* pInstance = new UI;
    pInstance->Initialize(info);

    return pInstance;
}
