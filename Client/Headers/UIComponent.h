#pragma once
#include "MonoBehavior.h"
#include "UI.h"

class UIComponent abstract : public Engine::MonoBehavior
{
protected:
	explicit UIComponent(const wchar_t* name);
	virtual ~UIComponent() = default;

protected:
	UI* AddUI(const UI::UIInfo& info);
	UI::UIInfo CreateInfo(const wchar_t* name, const wchar_t* textureTag, int fixframe, const Vector3& position, const Vector3& scale, Engine::Transform* pParent);

public:
	void SetDontDestroyObjectUI(bool isActive);
	void SetActives(bool check);
	void DeleteUI();

private:
	void Free() override;

protected:
	std::vector<UI*> _UIs;
};