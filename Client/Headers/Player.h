#pragma once
#include "MonoBehavior.h"

namespace Engine
{
	class Animation;
	class FiniteStateMachine;
}
	class GridMovement;

class Player : public Engine::MonoBehavior
{
public:
	explicit Player(const wchar_t* name);
private:
	virtual ~Player() = default;

public:
	// MonoBehavior��(��) ���� ��ӵ�
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	GridMovement* _movement = nullptr;
	Engine::Animation* _pAnimation = nullptr;
	Engine::FiniteStateMachine* _pFSM = nullptr;
private:
	Vector3 _gridPosition = { 0.f,0.f,0.f };
};
