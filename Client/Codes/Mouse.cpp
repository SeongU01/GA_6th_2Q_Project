#include "Mouse.h"

// Component
#include "Collider.h"
#include "Card.h"

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
}

void Mouse::Update(const float& deltaTime)
{	
	POINT mousePoint{};
	GetCursorPos(&mousePoint);
	ScreenToClient(_hWnd, &mousePoint);

	transform->position = Vector3((float)mousePoint.x, (float)mousePoint.y, 0.f);
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
			_hoverCard->SetHover(true);
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
			_hoverCard->SetHover(false);
			_hoverCard = nullptr;
		}
	}
}
