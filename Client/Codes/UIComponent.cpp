#include "UIComponent.h"
#include "Client_Define.h"

UIComponent::UIComponent(const wchar_t* name)
	: MonoBehavior(name)
{
}

void UIComponent::AddUI(const UI::UIInfo& info)
{
	UI* pUI = UI::Create(info);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pUI);
	_UIs.push_back(pUI);
}

void UIComponent::SetDontDestroyObject(bool isActive)
{
	for (auto& ui : _UIs)
		ui->SetDontDestroyObject(isActive);
}
