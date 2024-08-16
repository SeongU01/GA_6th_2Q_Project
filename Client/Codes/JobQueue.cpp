#include "JobQueue.h"

// Component
#include "Card.h"

#include "Client_Define.h"

constexpr float OFFSET = 130.f;

JobQueue::JobQueue()
	: MonoBehavior(L"JobQueue")
{
}

void JobQueue::Awake()
{	
}

void JobQueue::Start()
{
}

void JobQueue::Update(const float& deltaTime)
{
	if (!_jobQueue.empty())
	{
		const Card::CardData& cardData = _jobQueue.front().second->_cardData;

		_jobQueue.front().first += deltaTime;
		if (_jobQueue.front().first >= cardData.delayBefore)
		{
			_jobQueue.front().second->ActiveEffect();
			_jobQueue.pop_front();

			if (!_jobQueue.empty())
				_jobQueue.front().first -= cardData.delayAfter;
		}
	}
}

void JobQueue::LateUpdate(const float& deltaTime)
{
}

void JobQueue::PushQueue(Card* pCard)
{
	_jobQueue.push_back(std::make_pair(0.f, pCard));
	SetJobQueuePosition();
}

void JobQueue::PopQueue(Card* pCard)
{
	_jobQueue.remove_if([pCard](const std::pair<float, Card*>& pair)->bool { return pair.second == pCard; });
	SetJobQueuePosition();
}

void JobQueue::SetJobQueuePosition()
{
	size_t size = _jobQueue.size();
	size_t index = 0;

	for (auto& card : _jobQueue)
	{
		card.second->SetFixPosition(Vector3(1820.f, 50.f + (size - index) * OFFSET, 0.f));
		index++;
	}
}
