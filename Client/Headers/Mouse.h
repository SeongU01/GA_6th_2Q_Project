#pragma once
#include "MonoBehavior.h"

class CardSystem;
class TimerSystem;
class Card;
class EventManager;
class Mouse : public Engine::MonoBehavior
{
public:
	explicit Mouse(const wchar_t* name);
private:
	virtual ~Mouse() = default;

public:
	// MonoBehavior을(를) 통해 상속됨
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

private:
	void OnCollisionEnter(Engine::CollisionInfo& info);
	void OnCollision(Engine::CollisionInfo& info);
	void OnCollisionExit(Engine::CollisionInfo& info);

private:
	TimerSystem*	_pTimerSystem = nullptr;
	EventManager*	_pEventManager = nullptr;
	CardSystem*		_pCardSystem = nullptr;
	Card*			_hoverCard = nullptr;
	HWND			_hWnd = nullptr;
	D2D1_POINT_2F	_linePoint[3];
	bool			_isLineDraw = false;
};

