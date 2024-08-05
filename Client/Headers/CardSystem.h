#pragma once
#include "Base.h"

namespace Engine
{
	class GameObject;
	class TextRenderer;
}

class CardSystem final : public Engine::Base, public Engine::SingleTon<CardSystem>
{
	using RichText = std::tuple<unsigned int, unsigned int, std::wstring, unsigned int>;
	using OptionValue = std::pair<int, int>;
	friend class SingleTon;

	enum EffectType { Test1, Test2, Test3 };
private:
	explicit CardSystem() = default;
	virtual ~CardSystem() = default;

public:
	bool LoadCard(const wchar_t* filePath);
	void SetRichText(int ID, Engine::TextRenderer* pTextRenderer);

private:
	bool LoadCardDataOptionID(const wchar_t* filePath);
	bool LoadCardDataOptionText(const wchar_t* filePath);
	bool LoadCardDataRichText(const wchar_t* filePath);
	bool LoadCardData(const wchar_t* filePath);

private:
	// Base을(를) 통해 상속됨
	void Free() override;

public:
	std::vector<Engine::GameObject*> _cards;
	std::vector<std::wstring> _texts;
	std::vector<std::list<RichText>> _richTexts;
	std::vector<OptionValue> _optionValues;
};