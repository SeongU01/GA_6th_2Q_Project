#include "Button.h"

#include "Client_Define.h"
Button::Button()
	:MonoBehavior(L"Button")
{

}

void Button::MouseUpdate()
{
	GetCursorPos(&_mousePosition);
	ScreenToClient(Engine::GetWindow(), &_mousePosition); 
}

void Button::Awake()
{

}

void Button::Start()
{
}

void Button::Update(const float& deltaTime)
{
	if (!IsActive())
		return;

	MouseUpdate();
	int x = _mousePosition.x, y = _mousePosition.y;
	
	if (x > _buttonRange.left && x < _buttonRange.right && y>_buttonRange.top && y < _buttonRange.bottom)
	{
		if (Input::IsKeyDown(Input::DIM_LB)&& GetOwner().IsActive())//Å¬¸¯
		{
			_onPressed();
		}
		else if(GetOwner().IsActive())
		{
			if (_isRepeat || (!_isRepeat && !_isExecute))
			{
				_onHover();
			}
			_isExecute = true;
		}
	}
	else 
	{
		_isExecute = false;
		_cancel();
	}
	
}

void Button::LateUpdate(const float& deltaTime)
{

}
