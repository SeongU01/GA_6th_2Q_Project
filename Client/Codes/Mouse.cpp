#include "Mouse.h"

// Component
#include "Collider.h"
#include "Card.h"
#include "CardSystem.h"

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
}

void Mouse::Start()
{
	Engine::GameObject* pObject = Engine::FindObject((int)LayerGroup::Player, L"Player", nullptr);
	if (pObject) _pCardSystem = pObject->GetComponent<CardSystem>();
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
		}
		else
		{
			if (Input::IsKeyDown(Input::DIM_LB))
				_hoverCard->isHold = true;

			if (_hoverCard->isHold)
				_hoverCard->transform.position = transform.position;

			if (Input::IsKeyUp(Input::DIM_LB))
			{
				_hoverCard->isHold = false;

				if (900.f > transform.position.y)
					_pCardSystem->ActiveCard(_hoverCard);
			}
			
			if (Input::IsKeyDown(Input::DIM_RB))
			{
				_hoverCard->isHold = false;
				_hoverCard->SetMouseHover(false);
				_hoverCard = nullptr;
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
			_hoverCard->isHold = false;
			_hoverCard->SetMouseHover(false);
			_hoverCard = nullptr;
		}
	}
}
