#include "CardSystem.h"
#include "CardManagement.h"

//Component
#include "Card.h"

#include "Client_Define.h"

constexpr float MAXWIDTH = 1100.f;
constexpr float CARDWIDTH = 200.f;

void CardSystem::Update(const float& deltaTime)
{
	int index = 0;
	size_t size = _handDeck.size();
	float width = size * CARDWIDTH;
	float maxWitdh = MAXWIDTH < width ? MAXWIDTH : width;
	float halfX = maxWitdh * 0.5f;
	float offsetX = maxWitdh / size;

	for (auto& card : _handDeck)
	{
		card->gameObject->SetActive(true);
		card->transform->position = Vector3(float(WINCX >> 1) + offsetX * 0.5f - halfX + (offsetX * index), 1000.f, 0.f);
		index++;
	}
}

void CardSystem::LateUpdate(const float& deltaTime)
{
	if (Input::IsKeyDown(DIK_O))
	{
		DrawCard();
	}

	if (Input::IsKeyDown(DIK_P))
	{
		MoveTo(1, _handDeck, _graveDeck);
	}
}

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

	return true;
}

void CardSystem::StartGame()
{
	CardManagement* pCardManagement = CardManagement::GetInstance();

	for (auto& cardID : _originDeck)
	{
		_currentDeck.push_back(pCardManagement->CloneCard(cardID));
		Engine::AddObjectInLayer((int)LayerGroup::Object, L"Card", _currentDeck.back()->gameObject);
		_currentDeck.back()->gameObject->SetActive(false);
	}
	
	// Card 셔플
	std::vector<Card*> cards(_currentDeck.begin(), _currentDeck.end());
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(cards.begin(), cards.end(), gen);
	_currentDeck.assign(cards.begin(), cards.end());
}

void CardSystem::DrawCard()
{
	if (_currentDeck.empty() || 10 == _handDeck.size())
		return;

	Card* pCard = _currentDeck.back();
	pCard->gameObject->SetActive(true);
	pCard->SetHand();

	_handDeck.push_back(pCard);
	_currentDeck.pop_back();
}

void CardSystem::MoveTo(int ID, std::list<Card*>& src, std::list<Card*>& dst)
{
	auto find_iter = std::find_if(src.begin(), src.end(), [ID](Card* card)->bool {return ID == card->ID; });

	if (find_iter == src.end())
		return;

	(*find_iter)->Reset();
	dst.push_back(*find_iter);
	src.erase(find_iter);
}

void CardSystem::Free()
{
}
