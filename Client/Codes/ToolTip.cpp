#include "ToolTip.h"
#include "Pannel.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"
#include "Client_Define.h"
ToolTip::ToolTip(const wchar_t* name)
	:MonoBehavior(name)
{
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
  
        _toolTipinfos.push_back(_info);
        ToolTipInfo& info = _toolTipinfos.back();
        
        if (position.x == 0 && position.y == 0)
        {
            position = info._leftTop ? Vector3{ 160.f, 80.f, 0.f } : Vector3{ -150.f, -100.f, 0.f };
        }
        int line = (info._content.length() % 19==0)? (info._content.length() / 19): (info._content.length() / 19) +1;
        float height = 80 + (float)(line * 20);
        //�ǳ�
        Pannel::PannelInfo pannelInfo;
        pannelInfo.parent = info._leftTop ? transform.GetParent() : &transform;
        pannelInfo.position = position; 
        pannelInfo.size = Vector3{ 300, height, 0}; //ũ��
        pannelInfo.fillColor = 0x00000000; //����
        pannelInfo.opacity = 0.5f;
        pannelInfo.outlineColor = 0xFF000000; //�׵θ� ����
        Pannel* pPannel = Pannel::Create(pannelInfo);
        //����
        Engine::TextRenderer* pTextRenderer = pPannel->AddComponent<Engine::TextRenderer>(L"Title", D2D1::ColorF::Red, 20.f, DWRITE_FONT_WEIGHT_BOLD);
        pTextRenderer->SetText(info._title.c_str());
        pTextRenderer->SetDrawRect(250.f, 0.f);//ũ��(����)
        pTextRenderer->SetOffset(Vector3(-120, -30.f-(line*7), 0.f));
        pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
        //����
        pTextRenderer = pPannel->AddComponent<Engine::TextRenderer>(L"Content", D2D1::ColorF::White, 15.f, DWRITE_FONT_WEIGHT_BOLD);
        pTextRenderer->SetText(info._content.c_str());
        pTextRenderer->SetDrawRect(250.f, 0.f);//ũ��(����)
        pTextRenderer->SetOffset(Vector3(-120, 10.f - (line * 7), 0.f));//��ġ. (���� ���� ����. y�� üũ.
        pTextRenderer->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);

        Engine::AddObjectInLayer((int)LayerGroup::UI, L"ToolTip", pPannel);
        pPannel->SetRenderGroup((int)RenderGroup::UI);
        _toolTipList[info._id] = pPannel;

        pPannel->SetActive(false);
        return { position.x,position.y+ height+20,position.z };
        
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
