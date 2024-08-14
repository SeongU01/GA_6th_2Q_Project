#include "Mouse.h"

// Component
#include "Collider.h"
#include "Card.h"
#include "CardSystem.h"
#include "TimerSystem.h"
// timer
#include "TimerHUD.h"
#include "Client_Define.h"

Mouse::Mouse(const wchar_t* name)
	: MonoBehavior(name)
{
}

void Mouse::Awake()
{	
	Engine::Collider* pCollider = AddComponent<Engine::Collider>(L"Mouse");
	pCollider->SetScale(Vector3(10.f, 10.f, 0.f));

	_pOwner->_isDrawCollider = true;
	_hWnd = Engine::GetWindow();

	Engine::SpriteRenderer* pSpriteRenderer = GetComponent<Engine::SpriteRenderer>();
	pSpriteRenderer->SetOneSelfDraw(true, [=]()
		{
			if (_isLineDraw)
			{
				pSpriteRenderer->DrawTriangle(_linePoint[0], _linePoint[1], _linePoint[2], D2D1::ColorF::White, 0.75f);
			}
		});
}

void Mouse::Start()
{
	Engine::GameObject* pObject = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr);
	if (pObject) _pCardSystem = pObject->GetComponent<CardSystem>();
	_pTimerSystem = Engine::FindObject((int)LayerGroup::Player, L"Player", NULL)->GetComponent<TimerSystem>(); //타이머시스템
}

void Mouse::Update(const float& deltaTime)
{	
	POINT mousePoint{};
	GetCursorPos(&mousePoint);
	ScreenToClient(_hWnd, &mousePoint);

	mousePoint.x = std::clamp((int)mousePoint.x, 0, WINCX);
	mousePoint.y = std::clamp((int)mousePoint.y, 0, WINCY);
	transform.position = Vector3((float)mousePoint.x, (float)mousePoint.y, 0.f);
}

void Mouse::LateUpdate(const float& deltaTime)
{
	if (_hoverCard)
	{
		if (Input::IsKeyUp(Input::DIM_LB))
		{
			if (800.f > transform.position.y)
				_pCardSystem->ActiveCard(_hoverCard);
			_pTimerSystem->AddSkillTime(-1*_hoverCard->GetCostTime());
			_hoverCard->isHold = false;
			_hoverCard->SetMouseHover(false);
			_hoverCard = nullptr;
			_isLineDraw = false;
		}

		if (Input::IsKeyDown(Input::DIM_RB))
		{
			_pTimerSystem->AddSkillTime(-1 * _hoverCard->GetCostTime());
			_hoverCard->isHold = false;
			_hoverCard->SetMouseHover(false);
			_hoverCard = nullptr;
			_isLineDraw = false;
		}		
	}

	if (_isLineDraw)
		_linePoint[2] = { transform.position.x, transform.position.y };
}

void Mouse::OnCollisionEnter(Engine::CollisionInfo& info)
{	
}

void Mouse::OnCollision(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();

	if (*pOther == L"Card")
	{
		if (nullptr == _hoverCard)
		{
			_hoverCard = pOther->GetComponent<Card>();
			_hoverCard->SetMouseHover(true);
			_pTimerSystem->AddSkillTime(_hoverCard->GetCostTime());
		}
		else
		{
			if (Input::IsKeyDown(Input::DIM_LB))
			{
				_hoverCard->isHold = true;
				_linePoint[0] = { _hoverCard->transform.position.x - 10.f, _hoverCard->transform.position.y - 140.f };
				_linePoint[1] = { _hoverCard->transform.position.x + 10.f, _hoverCard->transform.position.y - 140.f };
				_isLineDraw = true;
			}
		}
	}
}

void Mouse::OnCollisionExit(Engine::CollisionInfo& info)
{
	Engine::GameObject* pOther = info.other->GetOwner();

	if (*pOther == L"Card")
	{
		if (pOther->GetComponent<Card>() == _hoverCard)
		{
			if (!Input::IsKeyPress(Input::DIM_LB))
			{
				_pTimerSystem->AddSkillTime(-1*_hoverCard->GetCostTime());
				_hoverCard->isHold = false;
				_hoverCard->SetMouseHover(false);
				_hoverCard = nullptr;
			}
		}
	}
}
