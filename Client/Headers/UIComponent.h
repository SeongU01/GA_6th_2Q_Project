#pragma once
#include "MonoBehavior.h"
#include "UI.h"

class UIComponent abstract : public Engine::MonoBehavior
{
protected:
	explicit UIComponent(const wchar_t* name);
	virtual ~UIComponent() = default;

protected:
	void AddUI(const UI::UIInfo& info);
	void SetDontDestroyObject(bool isActive);

private:
	std::list<UI*> _UIs;
};