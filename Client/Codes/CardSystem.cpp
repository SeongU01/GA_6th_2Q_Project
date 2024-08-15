#include "CardSystem.h"
#include "CardManager.h"

//Component
#include "Card.h"
#include "EventInvoker.h"
#include "GageHUD.h"

#include "Client_Define.h"

constexpr float MAXWIDTH = 1150.f;
constexpr float CARDWIDTH = 200.f;
constexpr float RELOADCOOLTIME = 3.f;

CardSystem::CardSystem()
	: MonoBehavior(L"CardSystem")
{	
}

void CardSystem::Awake()
{
	auto pGameObject = Engine::GameObject::Create();
	pGameObject->AddComponent<GageHUD>(Vector3(1680.f, 930.f, 0.f), &_reloadTime, RELOADCOOLTIME,1);
	pGameObject->SetRenderGroup(0);
	Engine::AddObjectInLayer((int)LayerGroup::UI, L"UI", pGameObject);

	_pEventInvoker = AddComponent<Engine::EventInvoker>(L"EventInvoker");
	LoadOriginDeck();
}

void CardSystem::Start()
{
	StartGame();
}

void CardSystem::Update(const float& deltaTime)
{
	_reloadTime = std::clamp(_reloadTime + deltaTime, 0.f, RELOADCOOLTIME);
}

void CardSystem::LateUpdate(const float& deltaTime)
{
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
	CardManager* pCardManager = CardManager::GetInstance();

	for (auto& cardID : _originDeck)
	{
		_currentDeck.push_back(pCardManager->CloneCard(cardID));
		Engine::AddObjectInLayer((int)LayerGroup::Object, L"Card", &_currentDeck.back()->gameObject);
		_currentDeck.back()->gameObject.SetActive(false);
	}

	_reloadTime = RELOADCOOLTIME;
	ShuffleCard();
	ReloadCard();
}

void CardSystem::DrawCard()
{
	if (_currentDeck.empty())
	{
		_currentDeck.assign(_graveDeck.begin(), _graveDeck.end());
		ShuffleCard();
	}

	Card* pCard = _currentDeck.back();
	pCard->gameObject.SetActive(true);
	pCard->DrawCard();

	_handDeck.push_back(pCard);
	_currentDeck.pop_back();

	SetHandDeckPosition();
}

void CardSystem::ReloadCard()
{
	if (_reloadTime >= RELOADCOOLTIME)
	{
		_pEventInvoker->BindAction(0.f, [this]() { this->ThrowCard(); });
		_reloadTime = 0.f;
	}
}

void CardSystem::OnReloadCoolTime()
{
	_reloadTime = RELOADCOOLTIME;
}

void CardSystem::ActiveCard(Card* pCard)
{
	if (pCard->AddJobQueue()) MoveTo(pCard, _handDeck, _graveDeck);
}

void CardSystem::MoveTo(Card* pCard, std::list<Card*>& src, std::list<Card*>& dst)
{
	auto find_iter = std::find_if(src.begin(), src.end(), [pCard](Card* card) -> bool
		{
			return (pCard == card);
		});

	if (find_iter == src.end())
		return;

	// (*find_iter)->Reset();
	dst.push_back(*find_iter);
	src.erase(find_iter);
	SetHandDeckPosition();
}

void CardSystem::ThrowCard()
{	
	if (_handDeck.empty())
	{		
		for (int i = 0; i < 5; i++)
		{
			_pEventInvoker->BindAction(0.2f + 0.1f * i, [this]() {this->DrawCard(); });
		}
		return;
	}

	Card* pCard = _handDeck.front();
	pCard->ThrowCard();
	_graveDeck.push_back(pCard);
	_handDeck.pop_front();
	_pEventInvoker->BindAction(0.05f, [this]() {this->ThrowCard(); });
}

void CardSystem::ShuffleCard()
{
	std::vector<Card*> cards(_currentDeck.begin(), _currentDeck.end());
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(cards.begin(), cards.end(), gen);
	_currentDeck.assign(cards.begin(), cards.end());
	_graveDeck.clear();
}

void CardSystem::SetHandDeckPosition()
{
	int index = 0;
	size_t size = _handDeck.size();
	float width = size * CARDWIDTH;
	float maxWitdh = MAXWIDTH < width ? MAXWIDTH : width;
	float halfX = maxWitdh * 0.5f;
	float offsetX = maxWitdh / size;

	for (auto& card : _handDeck)
	{
		if (!card->isHold)
			card->SetFixPosition(Vector3(float(WINCX >> 1) + offsetX * 0.5f - halfX + (offsetX * index), 1000.f, 0.f));

		card->gameObject.SetActive(true);
		index++;
	}
}
