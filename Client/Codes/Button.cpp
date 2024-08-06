#include "Button.h"

#include "Client_Define.h"
Button::Button()
	:MonoBehavior(L"Button")
{

}

void Button::MouseUpdate()
{
	GetCursorPos(&_mousePosition);
	ScreenToClient(GetActiveWindow(), &_mousePosition); 
}

void Button::Awake()
{

}

void Button::Start()
{

}

void Button::Update(const float& deltaTime)
{
	MouseUpdate();
	int x = _mousePosition.x, y = _mousePosition.y;
	
	if (x > _buttonRange.left && x < _buttonRange.right && y>_buttonRange.top && y < _buttonRange.bottom)
	{
		if (Input::IsKeyDown(Input::DIM_LB))//Å¬¸¯
		{
			_onPressed();
		}
		else
		{
			_onHover();
		}
	}
	else 
	{
		_cancel();
	}
	
}

void Button::LateUpdate(const float& deltaTime)
{

}
