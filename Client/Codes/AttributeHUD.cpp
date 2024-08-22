#include "AttributeHUD.h"

// Component
#include "ToolTip.h"
#include "Button.h"
#include "Attribute.h"
#include "HP.h"
#include "PlayerMP.h"
#include "TextRenderer.h"

#include "Client_Define.h"

constexpr float MAXWIDTH = 200.f;

AttributeHUD::AttributeHUD(Attribute* pAttribute)
	: UIComponent(L"AttributeHUD"), _pAttribute(pAttribute)
{
}

void AttributeHUD::Awake()
{
	_pToolTip = AddComponent<ToolTip>(L"AttributeToolTip");
	Button* pBtn = AddComponent<Button>();
	Engine::GameObject& pOwner = transform.GetOwner();
	if (pOwner.GetComponent<PlayerMP>() != nullptr) 
		_pToolTip->DontDestoryToolTips();
	pBtn->SetOnHover([&pOwner] {
		ToolTip* pToolTip = pOwner.GetComponent<ToolTip>(L"AttributeToolTip");
		pToolTip->ActiveToolTip(true);
		});
	pBtn->SetCancel([&pOwner] { 
		ToolTip* pToolTip = pOwner.GetComponent<ToolTip>(L"AttributeToolTip");
		pToolTip->ActiveToolTip(false);
		});
	UI::UIInfo info;
	UI* pUI = nullptr;
	for (int i = 0; i < Attribute::State::End; i++)
	{
		pUI = AddUI(CreateInfo(L"Attribute", L"UI_HUD_Attribute", i, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 0.f }, &transform));
		Engine::TextRenderer* pTextRenderer = pUI->AddComponent<Engine::TextRenderer>(L"TextRenderer", 0XFFFFFF, 25.f);
		pTextRenderer->SetOffset(Vector3(0.f, -5.f, 0.f));
		pUI->SetNotAffectCamera(false);
	}

	SetActives(false);
}

void AttributeHUD::Start()
{
}

void AttributeHUD::Update(const float& deltaTime)
{
	_currDirectionX = this->transform.scale.x > 0 ? 1 : -1;
	GetComponent<Button>()->SetRange(transform.position, {100,100});
	std::vector<UI*> activeUIs;

	std::wstring str;
	Vector3 NextPos = Vector3{ 0.0f,0.0f,0.0f };
	if(_currDirectionX>0)
	{
		for (int i = 0; i < Attribute::State::End; i++)
		{
			str = L"State_Char_00" + std::to_wstring(i);
			if (_pAttribute->IsActiveState((unsigned long long)1 << (i + 1)))
			{
				_UIs[i]->SetActive(true);
				_UIs[i]->GetComponent<Engine::TextRenderer>()->SetText(std::to_wstring(_pAttribute->GetStack(i)).c_str());
				activeUIs.push_back(_UIs[i]);
				if (!_pToolTip->FindToolTip(str))
					NextPos = _pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(str), NextPos);
			}
			else
			{
				_UIs[i]->SetActive(false);
				_pToolTip->DeleteToolTip(str);
			}
		}
	}
	else
	{
		for (int i = Attribute::State::End-1; i >= 0; i--)
		{
			str = L"State_Char_00" + std::to_wstring(i);
			if (_pAttribute->IsActiveState((unsigned long long)1 << (i + 1)))
			{
				_UIs[i]->SetActive(true);
				_UIs[i]->GetComponent<Engine::TextRenderer>()->SetText(std::to_wstring(_pAttribute->GetStack(i)).c_str());
				activeUIs.push_back(_UIs[i]);
				if (!_pToolTip->FindToolTip(str))
					NextPos = _pToolTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(str), NextPos);
			}
			else
			{
				_UIs[i]->SetActive(false);
				_pToolTip->DeleteToolTip(str);
			}
		}
	}
	size_t size = activeUIs.size();
	float width = 40.f * size;
	float maxWitdh = MAXWIDTH < width ? MAXWIDTH : width;
	float halfX = maxWitdh * 0.5f;
	float offsetX = maxWitdh / size;

	for (size_t i = 0; i < size; i++)
	{
		activeUIs[i]->transform.position = Vector3(offsetX * 0.5f - halfX + (offsetX * i), 70.f, 0.f);
		if(_currDirectionX  < 0 )
		{
			activeUIs[i]->transform.scale = {-1.0f, 1.0f, 1.0f};
		} 
		else
		{
			activeUIs[i]->transform.scale = {1.0f, 1.0f, 1.0f};
		} 
	}
	_pToolTip->MirrorToolTip(_currDirectionX);
}

void AttributeHUD::LateUpdate(const float& deltaTime)
{
}


void AttributeHUD::RemoveAllToolTip()
{
	_pToolTip->RemoveAllToolTip();
}

void AttributeHUD::AttrubuteRemoveToolTip()
{
	_pToolTip->AttributeRemoveToolTips();
}
