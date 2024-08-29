#pragma once
#include "GameObject.h"
#include "Card.h"

namespace Engine
{
	class TextRenderer;
}

class Card;
class SelectCard;
class CardManager final : public Engine::GameObject, public Engine::SingleTon<CardManager>
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
	void StartSelectCardScene();
	Card* CloneCard(int ID);
	void AddCardID(int ID);

private:
	bool LoadCardDataOptionText(const wchar_t* filePath);
	bool LoadCardDataRichText(const wchar_t* filePath);
	bool LoadCardData(const wchar_t* filePath);
	bool LoadCardDataAction(const wchar_t* filePath);
	bool LoadSelectCardPool(const wchar_t* filePath);
	void CardPoolShuffle();

private:
	// Base을(를) 통해 상속됨
	void Free() override;

private:
	std::vector<Card::CardData> _cardDatas;
	std::vector<std::vector<Card::CardAction>> _cardActionDatas;
	std::vector<std::wstring> _texts;
	std::vector<std::list<RichText>> _richTexts;
	std::list<int> _cardIDs;

	SelectCard* _pSelectCard = nullptr;
};