#pragma once
#include "MonoBehavior.h"

class Card;
class JobQueue : public Engine::MonoBehavior
{
public:
	explicit JobQueue();
private:
	virtual ~JobQueue() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void ResetQueue();
	void PushQueue(Card* pCard);
	void PopQueue(Card* pCard);
	bool IsJobQueueEmpty() { return _jobQueue.empty(); }

private:
	void SetJobQueuePosition();

private:
	std::list<std::pair<float, Card*>> _jobQueue;
	bool _isTutorial = false;
};