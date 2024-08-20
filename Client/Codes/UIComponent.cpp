#include "UIComponent.h"
#include "Client_Define.h"

UIComponent::UIComponent(const wchar_t* name)
	: MonoBehavior(name)
{
}

UI* UIComponent::AddUI(const UI::UIInfo& info)
{
	UI* pUI = UI::Create(info);
	Engine::AddObjectInLayer((int)LayerGroup::UI, info.name, pUI);
	_UIs.push_back(pUI);
	return pUI;
}

UI::UIInfo UIComponent::CreateInfo(const wchar_t* name, const wchar_t* textureTag, int fixframe, const Vector3& position, const Vector3& scale, Engine::Transform* pParent)
{
	UI::UIInfo info;
	info.name = name;
	info.textureTag = textureTag;
	info.fixFrame = fixframe;
	info.position = position;
	info.scale = scale;
	info.pParent = pParent;

	return info;
}

void UIComponent::SetDontDestroyObjectUI(bool isActive)
{
	for (auto& ui : _UIs)
		ui->SetDontDestroyObject(isActive);
}

void UIComponent::SetActives(bool check)
{
	for (auto& ui : _UIs)
		ui->SetActive(check);
}

void UIComponent::DeleteUI()
{
	for (auto& ui : _UIs)
		ui->SetDead();
}

void UIComponent::Free()
{
}
