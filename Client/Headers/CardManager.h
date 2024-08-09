#pragma once
#include "Base.h"
#include "Card.h"

namespace Engine
{
	class GameObject;
	class TextRenderer;
}

class Card;
class CardManager final : public Engine::Base, public Engine::SingleTon<CardManager>
{
	using RichText = std::tuple<unsigned int, unsigned int, std::wstring, unsigned int>;
	friend class SingleTon;

	enum EffectType { Test1, Test2, Test3 };
private:
	explicit CardManager() = default;
	virtual ~CardManager() = default;
	NOCOPY(CardManager)

public:
	bool LoadCard(const wchar_t* filePath);
	void SetRichText(int ID, Engine::TextRenderer* pTextRenderer);
	Card* CloneCard(int ID);

private:
	bool LoadCardDataOptionText(const wchar_t* filePath);
	bool LoadCardDataRichText(const wchar_t* filePath);
	bool LoadCardData(const wchar_t* filePath);

private:
	// Base을(를) 통해 상속됨
	void Free() override;

private:
	std::vector<Card::CardData> _cardDatas;
	std::vector<std::wstring> _texts;
	std::vector<std::list<RichText>> _richTexts;
};