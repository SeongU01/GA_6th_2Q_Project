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
	void SetDontDestroyObject(bool isActive);
	UI::UIInfo CreateInfo(const wchar_t* name, const wchar_t* tag, int fixframe, Vector3 position, Vector3 scale, Engine::Transform* parent)
	{
		UI::UIInfo info;
		info.name = name;
		info.textureTag = tag;
		info.fixFrame = fixframe;
		info.position = position;
		info.scale = scale;
		info.pParent = parent;
		return info;
	}
public:
	void SetActives(bool check);

protected:
	std::vector<UI*> _UIs;
};