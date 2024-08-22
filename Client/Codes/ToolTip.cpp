#include "ToolTip.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "Client_Define.h"
ToolTip::ToolTip(const wchar_t* name)
	:MonoBehavior(name)
{
}

ToolTip::ToolTip(const wchar_t* name, float scale)
    :MonoBehavior(name), _scale(scale)
{
}

void ToolTip::DontDestoryToolTips()
{
    _isDontDestory = true;
}

void ToolTip::ActiveToolTip(bool _isTrue)
{
    for (auto toolTip:_toolTipList)
    {
        toolTip.second->SetActive(_isTrue);
    }
}
Vector3 ToolTip::AddToolTip(const ToolTipInfo& _info, Vector3 position)
{
    if (_toolTipList[_info._id] == nullptr) {
        int line = ((int)_info._content.length() % 20 == 0) ? ((int)_info._content.length() / 20) : ((int)_info._content.length() / 20) + 1;
        float height = 80 + (float)(line * 13);
        if (position.x == 0 && position.y == 0)
        {
            position = _info._leftTop ? Vector3{ 160.f, 150.f - height / 2, 0.f } : Vector3{ -150.f, -100.f - height / 223, 0.f };
        }
        //판넬

        Pannel::PannelInfo pannelInfo;
        pannelInfo.parent = _info._leftTop ? transform.GetParent() : &transform;
        pannelInfo.position = { position.x,position.y + height / 2,position.z };
        pannelInfo.size = Vector3{ 300, height, 0 }; //크기
        pannelInfo.fillColor = 0x00000000; //색상
        pannelInfo.opacity = 0.8f;
        pannelInfo.outlineColor = 0xFFFFFFFF; //테두리 색상
        _infos.push_back(Pannel::Create(pannelInfo));
        Pannel* pPannel = _infos.back();
        pPannel->transform.scale = { _scale,_scale,_scale };
        //제목 
        D2D1::ColorF customColor(static_cast<DWORD>(0xFFFFDB32));
        Engine::TextRenderer* pTextRenderer = pPannel->AddComponent<Engine::TextRenderer>(L"Title", customColor, 20.f, DWRITE_FONT_WEIGHT_BOLD);
        pTextRenderer->SetText(_info._title.c_str());
        pTextRenderer->SetDrawRect(250.f, 0.f); //크기(고정)
        pTextRenderer->SetOffset(Vector3(-125, -30.f - (line * 7), 0.f));
        pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
        //내용
        pTextRenderer = pPannel->AddComponent<Engine::TextRenderer>(L"Content", D2D1::ColorF::White, 15.f, DWRITE_FONT_WEIGHT_BOLD);
        pTextRenderer->SetText(_info._content.c_str());
        pTextRenderer->SetDrawRect(250.f, 0.f); //크기(고정)
        pTextRenderer->SetOffset(Vector3(-125, 5.f - (line * 7), 0.f));//위치. (왼쪽 정렬 고정. y축 체크.
        pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);

        Engine::AddObjectInLayer((int)LayerGroup::UI, L"ToolTip", pPannel);
        pPannel->SetRenderGroup((int)RenderGroup::ToolTip);
        _toolTipList[_info._id] = pPannel;
        if (_isDontDestory) pPannel->SetDontDestroyObject(true);
        pPannel->SetActive(false);
        return { position.x,position.y + height + 20,position.z };
    }
    return position;
}

void ToolTip::ClearToolTip()
{
    _toolTipList.clear();
}


void ToolTip::DeleteToolTip(std::wstring str)
{
    Vector3 startPos = { -150.f, -100.f, 0.f };
    if (_toolTipList.find(str) != _toolTipList.end())
    {
        _toolTipList[str]->SetDontDestroyObject(false);
        _toolTipList.erase(str);
    }
    for (auto toolTip : _toolTipList)
    {
        Pannel* tip = toolTip.second;
        tip->transform.SetPosition(startPos);
        startPos={ startPos.x,startPos.y + tip->GetSize().y + 20,startPos.z};
    }
}

void ToolTip::MirrorToolTip(int _direction)
{
    if(_direction>0)
    {
        for (auto iter : _toolTipList)
        {
            iter.second->transform.scale = { 1.f,1.f,1.f };
        }
    }
    else
    {
        for (auto iter : _toolTipList)
        {
            iter.second->transform.scale = { -1.f, 1.f, 1.f };
        }
    }
}

void ToolTip::RemoveAllToolTip()
{
    for (auto& toolTip : _toolTipList)
    {
        toolTip.second->SetDead();
    }
}

void ToolTip::SetSelectCardToolTipInfo()
{
    for (auto& toolTip : _toolTipList)
        toolTip.second->SetRenderGroup((int)RenderGroup::Fade);

    for (auto& toolTip : _toolTipList)
        toolTip.second->transform.scale = Vector3(1.7f, 1.7f, 0.f);

    Vector3 startPos = { -450.f, -300.f, 0.f };
    for (auto toolTip : _toolTipList)
    {
        Pannel* tip = toolTip.second;
        tip->transform.SetPosition(startPos);
        startPos = { startPos.x, startPos.y + 210.f, startPos.z };
    }
}

void ToolTip::Awake()
{
}

void ToolTip::Start()
{
}

void ToolTip::Update(const float& deltaTime)
{
}

void ToolTip::LateUpdate(const float& deltaTime)
{
}