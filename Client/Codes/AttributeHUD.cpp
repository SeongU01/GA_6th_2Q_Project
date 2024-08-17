#include "AttributeHUD.h"

// Component
#include "ToolTip.h"
#include "Button.h"
#include "Attribute.h"
#include "HP.h"

#include "Client_Define.h"

constexpr float MAXWIDTH = 200.f;

AttributeHUD::AttributeHUD(Attribute* pAttribute)
	: UIComponent(L"AttributeHUD"), _pAttribute(pAttribute)
{
}

void AttributeHUD::Awake()
{
	UI::UIInfo info;
	UI* pUI = nullptr;
	for (int i = 0; i < Attribute::State::End; i++)
	{
		pUI = AddUI(CreateInfo(L"Attribute", L"UI_HUD_Attribute", i, { 0.f, 0.f, 0.f }, { 1.f, 1.f, 0.f }, &transform));
		pUI->SetNotAffectCamera(false);


		std::wstring str = L"State_Char_00" + std::to_wstring(i);
		std::wstring tempStr = L"Attribute" + std::to_wstring(i);
		const wchar_t* strTitle = tempStr.c_str();

		ToolTip* _pTip = pUI->AddComponent<ToolTip>(strTitle);
		_pTip->AddToolTip(DataManager::GetInstance()->GetToolTipInfo(str), Vector3(200.0f, 10.0f, 0.0f));
		Button* pBtn = pUI->AddComponent<Button>();
		pBtn->SetOnHover([pUI, strTitle] {
			printf("¾È³ç");
			ToolTip* pToolTip = pUI->GetComponent<ToolTip>(strTitle);
			pToolTip->ActiveToolTip(true);
			});
		pBtn->SetCancel([pUI, strTitle] {
			ToolTip* pToolTip = pUI->GetComponent<ToolTip>(strTitle);
			pToolTip->ActiveToolTip(false);
			});
		// pUI->SetRenderGroup((int)RenderGroup::Object);
	}

	SetActives(false);
}

void AttributeHUD::Start()
{
}

void AttributeHUD::Update(const float& deltaTime)
{
	std::vector<UI*> activeUIs;

	for (int i = 0; i < Attribute::State::End; i++)
	{
		if (_pAttribute->IsActiveState((unsigned long long)1 << (i + 1)))
		{
			_UIs[i]->SetActive(true);
			activeUIs.push_back(_UIs[i]);
		}
		else
			_UIs[i]->SetActive(false);
	}

	size_t size = activeUIs.size();
	float width = 40.f * size;
	float maxWitdh = MAXWIDTH < width ? MAXWIDTH : width;
	float halfX = maxWitdh * 0.5f;
	float offsetX = maxWitdh / size;

	for (size_t i = 0; i < size; i++)
	{
		activeUIs[i]->transform.position = Vector3(offsetX * 0.5f - halfX + (offsetX * i), 70.f, 0.f);
		activeUIs[i]->GetComponent<Button>()->SetRange(transform.position + activeUIs[i]->transform.position, activeUIs[i]->GetSize());
	}
}

void AttributeHUD::LateUpdate(const float& deltaTime)
{
}