#include "CardSystem.h"
#include "CardManagement.h"

//Component
#include "Card.h"

#include "Client_Define.h"

bool CardSystem::LoadOriginDeck()
{
	std::wstring path = rootPath;
	std::wifstream file(path + L"Data/Card/DefaultDeck.csv");
	file.imbue(std::locale("en_US.UTF-8"));

	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false;
	}

	std::wstring line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::wstringstream wss(line);
		std::wstring token;

		std::getline(wss, token, L',');	
		_originDeck.push_back(_wtoi(token.c_str()));
	}
}

void CardSystem::StartGame()
{
	CardManagement* pCardManagement = CardManagement::GetInstance();

	for (auto& cardID : _originDeck)
	{
		_currentDeck.push_back(pCardManagement->CloneCard(cardID));
		Engine::AddObjectInLayer((int)LayerGroup::Object, L"Card", _currentDeck.back()->gameObject);
	}
}

void CardSystem::DrawCard()
{
	_handDeck.push_back(_currentDeck.back());
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
