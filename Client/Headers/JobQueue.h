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
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

public:
	void PushQueue(Card* pCard);
	void PopQueue(Card* pCard);

private:
	void SetJobQueuePosition();

private:
	std::list<std::pair<float, Card*>> _jobQueue;
};