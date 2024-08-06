#pragma once
#include "GameObject.h"

class Card;
class CardSystem : public Engine::GameObject, public Engine::SingleTon<CardSystem>
{
	friend class SingleTon;
private:
	explicit CardSystem() = default;
	virtual ~CardSystem() = default;
	NOCOPY(CardSystem)

public:
	size_t GetCurrentDeckSize() const { return _currentDeck.size(); }
	size_t GetGraveDeckSize() const { return _graveDeck.size(); }
	size_t GetExtraDeckSize() const { return _extraDeck.size(); }

public:
	void StartGame();
	void DrawCard();

private:
	void MoveTo(int ID, std::list<Card*>& src, std::list<Card*>& dst);

private:
	std::list<Card*> _originDeck;
	std::list<Card*> _currentDeck;
	std::list<Card*> _handDeck;
	std::list<Card*> _graveDeck;
	std::list<Card*> _extraDeck;
};

