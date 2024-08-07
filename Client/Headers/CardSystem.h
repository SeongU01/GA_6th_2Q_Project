#pragma once
#include "Base.h"

class Card;
class CardSystem : public Engine::Base, public Engine::SingleTon<CardSystem>
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
	void Update(const float& deltaTime);
	void LateUpdate(const float& deltaTime);

public:
	bool LoadOriginDeck();
	void StartGame();
	void DrawCard();

private:
	void MoveTo(int ID, std::list<Card*>& src, std::list<Card*>& dst);

private:
	// Base을(를) 통해 상속됨
	void Free() override;

private:
	std::vector<int> _originDeck;
	std::list<Card*> _currentDeck;
	std::list<Card*> _handDeck;
	std::list<Card*> _graveDeck;
	std::list<Card*> _extraDeck;

};

