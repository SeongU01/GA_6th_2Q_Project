#include "CardSystem.h"
#include "Card.h"

void CardSystem::StartGame()
{
	_currentDeck = _originDeck;
}

void CardSystem::DrawCard()
{
	_hand.push_back(_currentDeck.back());
	_currentDeck.pop_back();
}

void CardSystem::MoveTo(int ID, std::list<Card*>& src, std::list<Card*>& dst)
{
	auto find_iter = std::find_if(src.begin(), src.end(), [ID](Card* card)->bool {return ID == card->ID; });

	if (find_iter == src.end())
		return;

	dst.push_back(*find_iter);
	src.erase(find_iter);
}
