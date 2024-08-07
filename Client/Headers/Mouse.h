#pragma once
#include "MonoBehavior.h"

class Card;
class Mouse : public Engine::MonoBehavior
{
public:
	explicit Mouse(const wchar_t* name);
private:
	virtual ~Mouse() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	void OnCollisionEnter(Engine::CollisionInfo& info);
	void OnCollision(Engine::CollisionInfo& info);
	void OnCollisionExit(Engine::CollisionInfo& info);

private:
	Card* _hoverCard = nullptr;
};
